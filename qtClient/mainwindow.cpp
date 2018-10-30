#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    foreach (const qint32 baudRate, QSerialPortInfo::standardBaudRates()) {
           ui->cbBaudRate->addItem(QString::number(baudRate), baudRate);
       }
/*    ui->cbBaudRate->addItem(QLatin1String("9600"), QSerialPort::Baud1200);
    ui->cbBaudRate->addItem(QLatin1String("9600"), QSerialPort::Baud9600);

    ui->cbBaudRate->addItem(QLatin1String("19200"), QSerialPort::Baud19200);
    ui->cbBaudRate->addItem(QLatin1String("38400"), QSerialPort::Baud38400);
    ui->cbBaudRate->addItem(QLatin1String("115200"), QSerialPort::Baud115200);
//    ui->cbBaudRate->addItem(QLatin1String("Custom"));
*/
    // fill data bits
    ui->cbDataBits->addItem(QLatin1String("5"), QSerialPort::Data5);
    ui->cbDataBits->addItem(QLatin1String("6"), QSerialPort::Data6);
    ui->cbDataBits->addItem(QLatin1String("7"), QSerialPort::Data7);
    ui->cbDataBits->addItem(QLatin1String("8"), QSerialPort::Data8);
    ui->cbDataBits->setCurrentIndex(3);

    // fill parity
    ui->cbParity->addItem(QLatin1String("None"), QSerialPort::NoParity);
    ui->cbParity->addItem(QLatin1String("Even"), QSerialPort::EvenParity);
    ui->cbParity->addItem(QLatin1String("Odd"), QSerialPort::OddParity);
    ui->cbParity->addItem(QLatin1String("Mark"), QSerialPort::MarkParity);
    ui->cbParity->addItem(QLatin1String("Space"), QSerialPort::SpaceParity);


    // fill stop bits
    ui->cbStopBits->addItem(QLatin1String("1"), QSerialPort::OneStop);
/*    #ifdef Q_OS_WIN
    ui->cbStopBits->addItem(QLatin1String("1.5"), QSerialPort::OneAndHalfStop);
    #endif
*/
    ui->cbStopBits->addItem(QLatin1String("2"), QSerialPort::TwoStop);

    // fill flow control
    ui->cbFlowControl->addItem(QLatin1String("None"), QSerialPort::NoFlowControl);
    ui->cbFlowControl->addItem(QLatin1String("RTS/CTS"), QSerialPort::HardwareControl);
    ui->cbFlowControl->addItem(QLatin1String("XON/XOFF"), QSerialPort::SoftwareControl);

    _name = "ZClient"; // Имя для аутентификации
    _sok = new QTcpSocket(this);

    // Подключаем обработчики сообщений
    connect(_sok, SIGNAL(readyRead()), this, SLOT(onSokReadyRead()));
    connect(_sok, SIGNAL(connected()), this, SLOT(onSokConnected()));
    connect(_sok, SIGNAL(disconnected()), this, SLOT(onSokDisconnected()));
    connect(_sok, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(onSokDisplayError(QAbstractSocket::SocketError)));

    LoadCfg();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSokConnected()
{
    ui->pbConnect->setEnabled(false);
    ui->pbDisconnect->setEnabled(true);
    ui->btnSendFile->setEnabled(true);
    ui->btnSendMessage->setEnabled(true);
//    ui->bntGetParam->setEnabled(true);
    ui->btnSetParam->setEnabled(true);
    ui->btnSearchCOMPorts->setEnabled(true);

    _blockSize = 0;
    AddToLog("Connected to"+_sok->peerAddress().toString()+":"+QString::number(_sok->peerPort()),Qt::green);

    // Отправляем данные для идентификации
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << (quint16)0;
    out << (quint8)cmdAutchReq;
    out << ui->leName->text();
    _name = ui->leName->text();
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    // TODO: Сделать проверку на ошибку
    AddToLog("Send blok cmdAutchReq size:"+QString::number(_sok->write(block)));
    //qDebug() << "Send block cmdAutchReq size:" << QString::number(_sok->write(block));
}

void MainWindow::onSokDisconnected()
{
    ui->pbConnect->setEnabled(true);
    ui->pbDisconnect->setEnabled(false);
    ui->btnSendFile->setEnabled(false);
    ui->btnSendMessage->setEnabled(false);
//    ui->bntGetParam->setEnabled(false);
    ui->btnSetParam->setEnabled(false);
    ui->btnSearchCOMPorts->setEnabled(false);

    AddToLog("Disconnected from"+_sok->peerAddress().toString()+":"+QString::number(_sok->peerPort()), Qt::red);
}

void MainWindow::onSokReadyRead()
{
    QDataStream in(_sok);
    in.setVersion(QDataStream::Qt_4_8);

    //если считываем новый блок первые 2 байта это его размер
    if (_blockSize == 0) {
        //если пришло меньше 2 байт ждем пока будет 2 байта
        if (_sok->bytesAvailable() < (int)sizeof(quint16))
            return;
        //считываем размер (2 байта)
        in >> _blockSize;
        //qDebug() << "_blockSize now " << _blockSize;
    }
    //ждем пока блок прийдет полностью
    // TODO: А если не прийдет?:)
    if (_sok->bytesAvailable() < _blockSize)
        return;
    else
        //можно принимать новый блок
        _blockSize = 0;
    //3 байт - команда серверу
    quint8 command;
    QString msgcmd;
    in >> command;
    //qDebug() << "Received command " << command;

    switch (command)
    {
        case cmdAutchReq:
        {
            //считываем имя
            in >> _name;

            ui->btnSendFile->setEnabled(true);
            ui->btnSendMessage->setEnabled(true);
//            ui->bntGetParam->setEnabled(true);
            ui->btnSendMessage->setEnabled(true);
            ui->btnSetParam->setEnabled(true);
            ui->btnSearchCOMPorts->setEnabled(true);
            AddToLog("Подлючились как "+_name,Qt::green);
        }
        break;

        case cmdGetDeviceParam:
        {
            // Пришли параметры
            in >> _settings;
            AddToLog("Пришли параметры для " + _settings._name ,Qt::green);

            if( ui->cbPortName->findText(_settings._name ) == -1 )
                ui->cbPortName->addItem(_settings._name);
            ui->cbPortName->setCurrentText(_settings._name);

            if( ui->cbBaudRate->findData(_settings._baudRate) == -1 )
                ui->cbBaudRate->addItem(QString::number(_settings._baudRate), _settings._baudRate);
            ui->cbBaudRate->setCurrentIndex(ui->cbBaudRate->findData(_settings._baudRate));


            if( ui->cbDataBits->findData(_settings._dataBits) == -1 )
                ui->cbDataBits->addItem(QString::number(_settings._dataBits), _settings._dataBits);
            ui->cbDataBits->setCurrentIndex(ui->cbDataBits->findData(_settings._dataBits));


            if( ui->cbFlowControl->findData(_settings._flowControl) == -1 )
                ui->cbFlowControl->addItem(QString::number(_settings._flowControl), _settings._flowControl);
            ui->cbFlowControl->setCurrentIndex(ui->cbFlowControl->findData(_settings._flowControl));

            if( ui->cbParity->findData(_settings._parity) == -1 )
                ui->cbParity->addItem(QString::number(_settings._parity));
            ui->cbParity->setCurrentIndex(ui->cbParity->findData(_settings._parity));


            if( ui->cbStopBits->findData(_settings._stopBits) == -1 )
                ui->cbStopBits->addItem(QString::number(_settings._stopBits));
            ui->cbStopBits->setCurrentIndex(ui->cbStopBits->findData(_settings._stopBits));

            ui->chOpened->setChecked(_settings._bIsOpen);

        }
        break;

        case cmdSetDeviceParam:
        {
            // Пришел ответ о параметрах
            QString message;
            in >> message;
            AddToLog("[Параметры]: "+message, Qt::blue);
        }
        break;

        case cmdMsgErrorToClient:
        {
            // Пришло сообщение об ошибке
            QString message;
            in >> message;
            AddToLog("[Параметры]: "+message, Qt::red);
        }
        break;

        case cmdMsgInfoToClient:
        {
            // Пришло сообщение от сервера
            QString message;
            in >> message;
            AddToLog("[Параметры]: "+message, Qt::blue);
        }
        break;

        case cmdGetDeviceList:
        {
            // Пришло сообщение о новом порте
            QString message;
            in >> message;
            ui->cbPortName->addItem(message);
            AddToLog("[Новый порт]: "+message, Qt::blue);
        }
        break;

        case cmdGetDeviceData:
        {
            // Пришли данные с устройства
            QString message;
            in >> message;

            AddToLog("[Данные с устройства]: "+message, Qt::blue);
            ui->lbComLog->insertItem(0, QTime::currentTime().toString()+" "+message);
        }
        break;

    default:
        AddToLog("Неизвестная команда: "+ QString::number( command ), Qt::red);
        in >> msgcmd;
        AddToLog("Сообщение: "+ msgcmd, Qt::red);
    }
}

void MainWindow::onSokDisplayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, "Ошибка", "Сервер не найден!");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, "Ошибка", "Сервер отклонил соединение!");
        break;
    default:
        QMessageBox::information(this, "Ошибка", "Ошибка: "+_sok->errorString());
    }
}

void MainWindow::on_pbConnect_clicked()
{
    _sok->connectToHost(ui->leHost->text(), ui->sbPort->value());
}

void MainWindow::on_pbDisconnect_clicked()
{
    _sok->disconnectFromHost();
}

void MainWindow::AddToLog(QString text, QColor color)
{
    ui->lwLog->insertItem(0, QTime::currentTime().toString()+" "+text);
    ui->lwLog->item(0)->setTextColor(color);
}

void MainWindow::on_btnSendMessage_clicked()
{
    if( ui->leMessage->text().isEmpty() )
            return;

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly); 
    out.setVersion(QDataStream::Qt_4_8);
    out << (quint16)0;
    //out << (quint8)cmdMsgFromClient;
    out << (quint8)cmdSendDeviceData;
    out << ui->leMessage->text();

    // если пустая команда то ошибка!!!!!!!
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    // TODO: Сделать проверку на ошибку
    AddToLog("Send blok cmdSendDeviceData size:"+QString::number(_sok->write(block)));
    // qDebug() << "Send block cmdMsgFromClient size:" <<  QString::number(_sok->write(block));
    //ui->leMessage->clear();
}

void MainWindow::on_btnSendFile_clicked()
{

    // TODO: Доделать
    if( ui->leFileName->text().isEmpty() )
            return;

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << (quint16)0;

    out << (quint8)cmdFileFromClient;


    out << ui->leFileName->text();

    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    // TODO: Сделать проверку на ошибку
    AddToLog("Send blok cmdFileFromClient size:"+QString::number(_sok->write(block)));
    //qDebug() << "Send block cmdFileFromClient size:" <<  QString::number(_sok->write(block));

}

void MainWindow::on_pushButton_clicked()
{
    // TODO: Выбрать файл
}

void MainWindow::on_bntGetParam_clicked()
{
    // TODO: Доделать
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << (quint16)0;
    out << (quint8)cmdGetDeviceParam;

    // тут отправлят имя устройства чьи мы параметры хотим получить

    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    // TODO: Сделать проверку на ошибку
    AddToLog("Send blok cmdServerParam size:"+QString::number(_sok->write(block)));
    //qDebug() << "Send block cmdFileFromClient size:" <<  QString::number(_sok->write(block));
}

void MainWindow::on_btnSetParam_clicked()
{
    qDebug() << "Set cmdSetDeviceParam";
    // тут отправляем параметры устройства клиенту
    // отправляем клиенту параметры

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    //резервируем место под размер блока
    out << (quint16)0;
    out << (quint8)cmdSetDeviceParam;
    // Получаем параметры для устройства
    out << _settings;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    //отправляем клиенту

    // TODO: Сделать проверку на ошибку
    AddToLog("Send blok cmdSetDeviceParam size:"+QString::number(_sok->write(block)));
    //qDebug() << "Send block cmdFileFromClient size:" <<  QString::number(_sok->write(block));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    SaveCfg();
}

void MainWindow::LoadCfg()
{
    // Загружаем и выставляем настройки
    QSettings settings( QCoreApplication::applicationDirPath() + "\\settings.conf", QSettings::IniFormat);
    ui->leHost->setText(settings.value("Main/Host", "127.0.0.1").toString());
    ui->sbPort->setValue(settings.value("Main/Port", 8080).toInt());
    ui->leName->setText(settings.value("Main/Name", "MyName").toString());

}

void MainWindow::SaveCfg()
{
    // Сохраняем настройки
    QSettings settings( QCoreApplication::applicationDirPath() + "\\settings.conf", QSettings::IniFormat);
    settings.setValue("Main/Host", ui->leHost->text() );
    settings.setValue("Main/Port", ui->sbPort->value() );
    settings.setValue("Main/Name", ui->leName->text() );
    settings.sync();
}


void MainWindow::on_btnSearchCOMPorts_clicked()
{
    // Очищаем список устройст перед запросом
    ui->cbPortName->clear();
    // Тут отправляем команду на получение списка устройств
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << (quint16)0;
    out << (quint8)cmdGetDeviceList;

    // если пустая команда то ошибка!!!!!!!
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    // TODO: Сделать проверку на ошибку
    AddToLog("Send blok cmdGetDeviceList size:"+QString::number(_sok->write(block)));
}


void MainWindow::on_cbStopBits_currentIndexChanged(int index)
{
    _settings._stopBits = ui->cbStopBits->itemData(index).toInt();
}

void MainWindow::on_cbFlowControl_currentIndexChanged(int index)
{
    _settings._flowControl = ui->cbFlowControl->itemData(index).toInt();
}

void MainWindow::on_cbParity_currentIndexChanged(int index)
{
    _settings._parity = ui->cbParity->itemData(index).toInt();
}


void MainWindow::on_cbDataBits_currentIndexChanged(int index)
{
    _settings._dataBits = ui->cbDataBits->itemData(index).toInt();
}

void MainWindow::on_cbBaudRate_activated(const QString &arg1)
{
    _settings._baudRate = arg1.toInt();
}

void MainWindow::on_cbPortName_activated(const QString &arg1)
{
    _settings._name = arg1;
}
