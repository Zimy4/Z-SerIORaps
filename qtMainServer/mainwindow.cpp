#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&serv, SIGNAL(AddLogMessage(QString,QColor)), this, SLOT(onAddLogMessage(QString,QColor)));

    // Заполняем список устройств
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        ui->cbListDevices->addItem("/dev/"+info.portName());

    ui->cbListDevices->setCurrentIndex(0);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    serv.doStopServer();
}


void MainWindow::onAddLogMessage(QString text, QColor color)
{
    ui->lbServerLog->insertItem(0, QTime::currentTime().toString()+" "+text);
    ui->lbServerLog->item(0)->setTextColor(color);
}

void MainWindow::on_btnStartServer_clicked()
{
    if ( serv.doStartServer(QHostAddress::Any, ui->sbNumServerPort->value(), ui->cbListDevices->currentText()) )
    {
        ui->btnStartServer->setEnabled( false );
        ui->btnStopServer->setEnabled( true );
        ui->cbListDevices->setEnabled( false );
    }
    else
    {
        ui->btnStartServer->setEnabled( true );
        ui->btnStopServer->setEnabled( false );
        ui->cbListDevices->setEnabled( true );
    }
}

void MainWindow::on_btnStopServer_clicked()
{
    if ( serv.doStopServer() )
    {
        ui->btnStartServer->setEnabled( true );
        ui->btnStopServer->setEnabled( false );
        ui->cbListDevices->setEnabled( true );
    }
    else
    {
        ui->btnStartServer->setEnabled( false );
        ui->btnStopServer->setEnabled( true );
        ui->cbListDevices->setEnabled( false );
    }
}
