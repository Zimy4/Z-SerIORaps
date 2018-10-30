#include "rpiserver.h"

CRpi3Server::CRpi3Server(QObject *parent, CRPI3Serial *device) :
    QTcpServer(parent),
    _sok(NULL),
    _device(device)
{
    qDebug("Device: %p", _device);
    connect(this, SIGNAL(newConnection()), this, SLOT(onConnection())); // подключаем сигнал "новое подключение" к нашему обработчику подключений
    _blockSize = 0;
}

bool CRpi3Server::doStartServer(QHostAddress addr, qint16 port)
{
    if (!listen(addr, port))
    {
        qDebug() << "Server not started at" << addr << ":" << port;
        return false;
    }
    qDebug() << "Server started at" << addr << ":" << port;
    return true;
}

bool CRpi3Server::doStopServer()
{
    if(isListening())
    {
        // сначала отключаем все соеденения
        if(_sok)
        {
            qDebug() << "Socket close";
            _sok->close();
            _sok = NULL;
        }
        qDebug() << "Server stop listening ";
        close();
    }
    return true;//(server->isListening());
}

void CRpi3Server::onConnection() // обработчик подключений
{  
    QTcpSocket *socket = this->nextPendingConnection(); // получаем сокет нового входящего подключения
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChanged(QAbstractSocket::SocketState))); // делаем обработчик изменения статуса сокета

    if (!_sok) { // если у нас нет "вещающего", то данное подключение становится вещающим
        connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead())); // подключаем входящие сообщения от вещающего на наш обработчик
        connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));
        //socket->write("server"); // говорим ему что он "вещает"
        _sok = socket; // сохраняем себе"
        qDebug() << "this one is server";
        //sendToClient(_sok, "");
    }
    else {
        // иначе говорим подключенному что он не нужен
        socket->abort();
    }
}

void CRpi3Server::onReadyRead() // обработчик входящих сообщений от "вещающего"
{    
    qDebug() << "onReadyRead ";
    QObject * object = QObject::sender(); // далее и ниже до цикла идет преобразования "отправителя сигнала" в сокет, дабы извлечь данные
    if (!object)
        return;

    QTcpSocket *pClientSocket = static_cast<QTcpSocket *>(object);
    if (!pClientSocket)
        return;

    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_4_8);

    // если считываем новый блок первые 2 байта это его размер
    if (_blockSize == 0) {
        //если пришло меньше 2 байт ждем пока будет 2 байта
        if (pClientSocket->bytesAvailable() < (int)sizeof(quint16))
            return;
        qDebug() << "bytesAvailable now " << pClientSocket->bytesAvailable();
        //считываем размер (2 байта)
        in >> _blockSize;
        qDebug() << "_blockSize now " << _blockSize;
    }
    //ждем пока блок прийдет полностью
    if (pClientSocket->bytesAvailable() < _blockSize)
        return;
    else
        _blockSize = 0;

    //3 байт - команда серверу
    quint8 command;
    in >> command;
    qDebug() << "Received command " << command;

    switch(command)
    {
        case cmdAutchReq:
        {
            qDebug() << "Get cmdAutchReq command";
            //считываем имя
            QString name;
            in >> name;            
            // TODO: тит проверяем что имя наше
            //авторизация пройдена
            // отправляем клиенту его имя
            QByteArray block;
            QDataStream out(&block, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_4_8);
            //резервируем место под размер блока
            out << (quint16)0;
            out << (quint8)cmdAutchReq;
            out << name;
            //пишем на зарезервированное место размер блока
            out.device()->seek(0);
            out << (quint16)(block.size() - sizeof(quint16));
            //отправляем клиенту
            qDebug() << "Send name with cmdAutchReq command size: "  << QString::number( pClientSocket->write(block) );
        }
        break;

        case cmdMsgFromClient:
        {        
            // тут принимаем сообщение
            QString msg;
            in >> msg;
            qDebug() << "Get cmdMsgFromClient" << msg;
            QByteArray d;
            d.append(msg);
            emit SendDataToDevice(d);
        }
        break;

        case cmdFileFromClient:
        {
            QString msg;
            in >> msg;
            qDebug() << "Get cmdFileFromClient" << msg;
            // тут принимаем файл
        }
        break;

        case cmdServerParam:
        {
            qDebug() << "Get cmdServerParam";
            // тут отправляем параметры устройства клиенту
            // отправляем клиенту параметры
            QByteArray block;
            QDataStream out(&block, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_4_8);
            //резервируем место под размер блока
            out << (quint16)0;
            out << (quint8)cmdServerParam;
            out << "BITRATE|48000|BIT|16|XON|12";
            //пишем на зарезервированное место размер блока
            out.device()->seek(0);
            out << (quint16)(block.size() - sizeof(quint16));
            //отправляем клиенту
            qDebug() << "Send params with cmdServerParam command, size: "  << QString::number( pClientSocket->write(block) );
        }
        break;
    default:
        //
        qDebug() << "Неизвестная команда: " + QString::number( command );
        QString msg;
        in >> msg;
        qDebug() << "Сообщение: " + msg;
    }

    //for (long long i = 0; i < 4000000000; ++i){}
}
void CRpi3Server::stateChanged(QAbstractSocket::SocketState state) // обработчик статуса, нужен для контроля за "вещающим"
{
    QObject * object = QObject::sender();
    if (!object)
        return;
    QTcpSocket * socket = static_cast<QTcpSocket *>(object);
    qDebug() << state;
    if (socket == _sok && state == QAbstractSocket::UnconnectedState)
        _sok = NULL;
}

void CRpi3Server::GetDataFromDevice(QString data)
{
    qDebug() << "Get data from Serial: " << data;
}
