#include "rpi3server.h"

CRpi3Server::CRpi3Server(QObject *parent) :
    QTcpServer(parent),
    _sok(NULL)
{
    qDebug("Init Server: %p", this);
    // подключаем сигнал "новое подключение" к нашему обработчику подключений
    connect(this, SIGNAL(newConnection()), this, SLOT(onConnection()));
    _blockSize = 0;
    _addr = QHostAddress::Any;
    _port = 8080;

    // TODO: Считываем настройки с файла
    LoadCFG();

    // Но пока так

    _cfgDevice._name = "/dev/ttyAMA0";
    _cfgDevice._baudRate = QSerialPort::Baud9600;
    _cfgDevice._dataBits = QSerialPort::Data8;
    _cfgDevice._flowControl = QSerialPort::NoFlowControl;
    _cfgDevice._parity = QSerialPort::NoParity;
    _cfgDevice._stopBits = QSerialPort::OneStop;
    _cfgDevice._bIsOpen = false;

    _device.setPortName(_cfgDevice._name);
    _device.setBaudRate((QSerialPort::BaudRate)_cfgDevice._baudRate);
    _device.setDataBits((QSerialPort::DataBits)_cfgDevice._dataBits);
    _device.setFlowControl((QSerialPort::FlowControl)_cfgDevice._flowControl);
    _device.setParity((QSerialPort::Parity)_cfgDevice._parity);
    _device.setStopBits((QSerialPort::StopBits)_cfgDevice._stopBits);
    _cfgDevice._bIsOpen = _device.isOpen();


    qDebug() << "List of ports:";
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        qDebug() <<  "/dev/"+info.portName();
    }

}

CRpi3Server::~CRpi3Server()
{      
    _device.close();    
    SaveCFG();
}

bool CRpi3Server::doStartServer(QHostAddress addr, qint16 port)
{
    // Стартуем сервер
    if (!listen(addr, port))
    {
        qDebug() << "Server NOT started at" << addr << ":" << port;
        return false;
    }
    qDebug() << "Server started at" << addr << ":" << port;

    // TODO: Здесь так же подключаемся к устройству
    // Стартуем устройство
    if ( !_device.open(QSerialPort::ReadWrite) )
    {
        // TODO: Тут ругаемся!
        qDebug() << "Device" << _device.portName() << " open fail! ";
        //
    }
    else
    {
        qDebug() << "Device on " << _device.portName() << " connected!";
        _device.clear();
    }

    connect(&_device, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(onDeviceError(QSerialPort::SerialPortError)));
    connect(&_device, SIGNAL(readyRead()), this, SLOT(GetDataFromDevice()));

    _cfgDevice._bIsOpen = _device.isOpen();

    return true;
}

bool CRpi3Server::doStopServer()
{
    qDebug() << "Stop server...";

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

    // Отключаем устройство
    _device.close();

    return true;
}

void CRpi3Server::SendMessageToClient(quint8 command, const QString &str)
{
    // тут отправляем параметры устройству
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    //резервируем место под размер блока
    out << (quint16)0;
    out << (quint8)command;
    out << str;
    //пишем на зарезервированное место размер блока
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    //отправляем клиенту
    if (_sok )
    {
        qDebug() << "SendMessageToClient " << QString::number(command) << " command size: "  << QString::number( _sok->write(block) );
        _sok->waitForBytesWritten(500);
    }
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
        qDebug() << "Client connected!";
        //sendToClient(_sok, "");
    }
    else {
        // иначе говорим подключенному что он не нужен
        qDebug() << "Abort connetction(Clients is connected)!";
        socket->abort();
    }
}

void CRpi3Server::onReadyRead() // обработчик входящих сообщений от "вещающего"
{    
    QObject * object = QObject::sender(); // далее и ниже до цикла идет преобразования "отправителя сигнала" в сокет, дабы извлечь данные
    if (!object)
        return;

    QTcpSocket *pClientSocket = static_cast<QTcpSocket *>(object);
    if (!pClientSocket)
        return;

    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_4_8);

//    qDebug() << "onReadyRead ";

    // если считываем новый блок первые 2 байта это его размер
    if (_blockSize == 0) {
        //если пришло меньше 2 байт ждем пока будет 2 байта
        if (pClientSocket->bytesAvailable() < (int)sizeof(quint16))
            return;
//        qDebug() << "bytesAvailable now " << pClientSocket->bytesAvailable();
        //считываем размер (2 байта)
        in >> _blockSize;
//        qDebug() << "_blockSize now " << _blockSize;
    }
    //ждем пока блок прийдет полностью
    if (pClientSocket->bytesAvailable() < _blockSize)
        return;
    else
        _blockSize = 0;

    //3 байт - команда серверу
    quint8 command;
    in >> command;
//    qDebug() << "Received command " << command;

    switch(command)
    {
        case cmdAutchReq:
        {
            qDebug() << "Get cmdAutchReq command:";
            //считываем имя
            QString name;
            in >> name;
            // FIXME: тут проверяем что имя наше
            // авторизация пройдена
            // отправляем клиенту его имя
            SendMessageToClient(cmdAutchReq, "Auth - OK!");
/*            QByteArray block;
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
*/
        }
        break;

        case cmdMsgFromClient:
        {        
            // тут принимаем сообщение для устройства
            QString msg;
            in >> msg;
            qDebug() << "Get cmdMsgFromClient:" << msg;
            QByteArray d;
            d.append(msg);

            if(_device.isOpen()) {
                qDebug() << "Send bytes to device:" << QString::number( _device.write(d) );
            }
            else
            {
                // TODO: Сообщаем об ошибке
                QString msg;
                msg = "Error send command to device: "+_device.portName() + "not open!";
                qDebug() << msg;
                SendMessageToClient(cmdMsgErrorToClient, msg );
            }
            // TODO: Отправляем на устройство сообщение
            // emit SendDataToDevice(d);
        }
        break;

        case cmdFileFromClient:
        {
            QString msg;
            in >> msg;
            qDebug() << "Get cmdFileFromClient:" << msg;
            // тут принимаем файл
            // TODO: Отправляем на устройство файл
        }
        break;

        case cmdGetDeviceParam:
        {
            // Пришел запрос на текущие параметры устройства
            qDebug() << "Get cmdGetDeviceParam:";
            QString port;
            in >> port;
            qDebug() << "Get device cfg :" << port;
            if ( port != "" )
            {
                // если пришел запрос на параметры порта отличного от используемого
                // TODO: Мы должны открыть новый порт и получить новые параметры!
                qDebug() << "Get cfg on port:" << port;

            }
            // TODO: отправляем клиенту параметры ВЫБРАННОГО ПОРТА
            QByteArray block;
            QDataStream out(&block, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_4_8);
            //резервируем место под размер блока
            out << (quint16)0;
            out << (quint8)cmdGetDeviceParam;
            // TODO: Получаем параметры устройства            
            out << _cfgDevice;
            out.device()->seek(0);
            out << (quint16)(block.size() - sizeof(quint16));
            //отправляем клиенту
            qDebug() << "Send params with cmdGetDeviceParam command, size: "  << QString::number( pClientSocket->write(block) );
        }
        break;

        case cmdSetDeviceParam:
        {
            // Пришел запрос на установку параметров устройства
            qDebug() << "Get cmdSetDeviceParam:";
            // Пришли параметры
            CSettingsDevice _settings;
            in >> _settings;
            // TODO: Тут пробуем применить параметры и открыть устройство
            if( !SetCfgDevice(_settings) )
            {
                SendMessageToClient(cmdMsgErrorToClient, "Error apply new cfg for device!");
                return;
            }
            SendMessageToClient(cmdMsgInfoToClient, "New config for device - OK!");
        }
        break;

        case cmdGetDeviceList:
        {
            // Пришел запрос на получение списка устройств
            qDebug() << "Get cmdGetDeviceList:";
            // Запрашиваем список устройств
            QString strPortName;
            foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
            {
                qDebug() <<  info.portName();
                strPortName = "/dev/" + info.portName();
                SendMessageToClient(cmdGetDeviceList, strPortName );
            }
        }
    break;

    default:
        //
        qDebug() << "Unknow command: " + QString::number( command );
        QString msg;
        in >> msg;
        qDebug() << "Message: " + msg;
    }

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

void CRpi3Server::GetDataFromDevice()
{
    //Чтение данных из порта
    QByteArray data;   
    data.append(_device.readAll());
    QString msg;
    msg.append(data);
    qDebug() << "Get data from Serial: " << msg;

    // TODO: Отправляем клиенту ответ что получены данные
    SendMessageToClient(cmdGetDeviceData, msg);

}

bool CRpi3Server::SetCfgDevice(CSettingsDevice &cfg)
{
    // Устанавливаем новые параметры устройства
    qDebug() << "Set new settings to device: " << cfg._name;
    _device.close();

    _device.setPortName(cfg._name);
    _device.setBaudRate((QSerialPort::BaudRate)cfg._baudRate);
    _device.setDataBits((QSerialPort::DataBits)cfg._dataBits);
    _device.setFlowControl((QSerialPort::FlowControl)cfg._flowControl);
    _device.setParity((QSerialPort::Parity)cfg._parity);
    _device.setStopBits((QSerialPort::StopBits)cfg._stopBits);

    if ( _device.open(QSerialPort::ReadWrite) )
    {
        qDebug() << "Apply new settings - OK! ";
        _cfgDevice = cfg;
        return true;
    }

    qDebug() << "Apply new settings - Fail! ";
    // TODO: Отправить ошибку клиенту

    return false;

}

void CRpi3Server::onDeviceError(QSerialPort::SerialPortError error)
{
    // Обработка ошибок с устройства
    if( _sok )
    {
        SendMessageToClient(cmdMsgErrorToClient, QString::number(error) + ":" + _device.errorString() );
    }
}

void CRpi3Server::SaveCFG()
{
    // Сохраняем настройки
    QSettings settings( QCoreApplication::applicationDirPath() + "\\settings.conf", QSettings::IniFormat);
    settings.setValue("Main/Host", QHostAddress(_addr).toString() );
    settings.setValue("Main/Port", _port );
    settings.sync();
}

void CRpi3Server::LoadCFG()
{
    // Загружаем и выставляем настройки
    QSettings settings( QCoreApplication::applicationDirPath() + "\\settings.conf", QSettings::IniFormat);    
    QString adress = settings.value("Main/Host", QHostAddress::Any).toString();
    qDebug() << adress;
    _addr = QHostAddress(adress);
    _port = settings.value("Main/Port", 8080).toInt();
}
