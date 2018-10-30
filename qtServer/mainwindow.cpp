#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    connect(ui->cbBaudRate, SIGNAL(currentIndexChanged(int)) ,this, SLOT(checkCustomBaudRatePolicy(int))); // Переделать в нормальный слот

    ui->cbBaudRate->addItem(QLatin1String("9600"), QSerialPort::Baud9600);
    ui->cbBaudRate->addItem(QLatin1String("19200"), QSerialPort::Baud19200);
    ui->cbBaudRate->addItem(QLatin1String("38400"), QSerialPort::Baud38400);
    ui->cbBaudRate->addItem(QLatin1String("115200"), QSerialPort::Baud115200);
    ui->cbBaudRate->addItem(QLatin1String("Custom"));

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
    #ifdef Q_OS_WIN
    ui->cbStopBits->addItem(QLatin1String("1.5"), QSerialPort::OneAndHalfStop);
    #endif
    ui->cbStopBits->addItem(QLatin1String("2"), QSerialPort::TwoStop);

    // fill flow control
    ui->cbFlowControl->addItem(QLatin1String("None"), QSerialPort::NoFlowControl);
    ui->cbFlowControl->addItem(QLatin1String("RTS/CTS"), QSerialPort::HardwareControl);
    ui->cbFlowControl->addItem(QLatin1String("XON/XOFF"), QSerialPort::SoftwareControl);


//    connect(ui->cBtnSend,SIGNAL(clicked()),this, SLOT(on_cEnterText_returnPressed()) );

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    QThread *threadComPort = new QThread;   // Создаем поток для работы с устройством
    CRPI3Serial *ComPort = new CRPI3Serial();        // Создаем обьект для работы с портом
    TCPTest = new CRpi3Server(this, ComPort);        //создаем сервер
    ComPort->moveToThread(threadComPort);   //помешаем класс  в поток
    ComPort->thisPort.moveToThread(threadComPort);  //Помещаем сам порт в поток

    connect(ComPort, SIGNAL(error_(QString)), this, SLOT(PrintCOMMessage(QString))); //Лог ошибок

    connect(threadComPort, SIGNAL(started()), ComPort, SLOT(process_Port()));   //Переназначения метода run
    connect(ComPort, SIGNAL(finished_Port()), threadComPort, SLOT(quit()));     //Переназначение метода выход
    connect(threadComPort, SIGNAL(finished()), ComPort, SLOT(deleteLater()));   //Удалить к чертям поток
    connect(ComPort, SIGNAL(finished_Port()), threadComPort, SLOT(deleteLater()));//Удалить к чертям поток
    connect(this, SIGNAL(savesettings(QString,int,int,int,int,int)),ComPort,SLOT(Write_Settings_Port(QString,int,int,int,int,int)));//Слот - ввод настроек!

    connect(ui->btnConnectCOM, SIGNAL(clicked()),ComPort,SLOT(ConnectPort()));
    connect(ui->btnDisconectCOM, SIGNAL(clicked()),ComPort,SLOT(DisconnectPort()));
    //connect(ComPort, SIGNAL(outPort(QString)), this, SLOT(PrintCOMMessage(QString))); //Лог ошибок
//    connect(this, SIGNAL(writeData(QByteArray)), ComPort, SLOT(WriteToPort(QByteArray)));
    connect(TCPTest, SIGNAL(SendDataToDevice(QByteArray)), ComPort, SLOT(WriteToPort(QByteArray)));
    connect(ComPort, SIGNAL(outPort(QString)), TCPTest, SLOT(GetDataFromDevice(QString)));
    threadComPort->start();
}

MainWindow::~MainWindow()
{
    delete TCPTest;
    delete ui;
}


void MainWindow::on_btnStartServer_clicked()
{
    if( TCPTest->doStartServer(QHostAddress::Any, ui->sbNumServerPort->value()) )
    {
        ui->btnStartServer->setEnabled( false );
        ui->btnStopServer->setEnabled( true );
        ui->lbServerLog->addItem("Server started");
    }

}

void MainWindow::on_btnStopServer_clicked()
{
    if( TCPTest->doStopServer() )
    {
        ui->btnStartServer->setEnabled( true );
        ui->btnStopServer->setEnabled( false );
        ui->lbServerLog->addItem("Server stoped! ");
    }

}

void MainWindow::on_cbBaudRate_currentIndexChanged(int index)
{
    bool isCustomBaudRate = !ui->cbBaudRate->itemData(index).isValid();
    ui->cbBaudRate->setEditable(isCustomBaudRate);
    if (isCustomBaudRate) {
        ui->cbBaudRate->clearEditText();
    }
}

void MainWindow::PrintCOMMessage(QString data)
{
    //TODO: тутнадо ловить ошибки с потока

    ui->lbComLog->addItem(data); // Вывод текста в консоль
}

void MainWindow::on_btnSearchCOMPorts_clicked()
{
    ui->cbPortName->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->cbPortName->addItem(info.portName());
    }
}

void MainWindow::on_btnSaveCOMSettings_clicked()
{
    savesettings(ui->cbPortName->currentText(), ui->cbBaudRate->currentText().toInt(),ui->cbDataBits->currentText().toInt(),
                 ui->cbParity->currentText().toInt(), ui->cbStopBits->currentText().toInt(), ui->cbFlowControl->currentText().toInt());
}


void MainWindow::on_btnTest_clicked()
{

}
