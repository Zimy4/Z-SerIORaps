#include "crpi3serial.h"

CRPI3Serial::CRPI3Serial(QObject *parent)
    : QObject(parent)
{

}

CRPI3Serial::~CRPI3Serial()
{
    // тут все закрываем
    qDebug("By in Thread!");
    emit finished_Port();//Сигнал о завершении работы
}

void CRPI3Serial::process_Port()
{
    //Выполняется при старте класса
    qDebug("Hello World in Thread!");
    connect(&thisPort, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError))); // подключаем проверку ошибок порта
    connect(&thisPort, SIGNAL(readyRead()), this, SLOT(ReadInPort()));//подключаем   чтение с порта по сигналу readyRead()
}

void CRPI3Serial::Write_Settings_Port(QString name, int baudrate,int DataBits,
                         int Parity,int StopBits, int FlowControl)
{
    //заносим параметры порта в структуру данных
    SettingsPort.name = name;
    SettingsPort.baudRate = (QSerialPort::BaudRate) baudrate;
    SettingsPort.dataBits = (QSerialPort::DataBits) DataBits;
    SettingsPort.parity = (QSerialPort::Parity) Parity;
    SettingsPort.stopBits = (QSerialPort::StopBits) StopBits;
    SettingsPort.flowControl = (QSerialPort::FlowControl) FlowControl;
}

void CRPI3Serial::ConnectPort(void)
{
    //процедура подключения
    thisPort.setPortName(SettingsPort.name);
    if (thisPort.open(QIODevice::ReadWrite)) {
        if (thisPort.setBaudRate(SettingsPort.baudRate)
                && thisPort.setDataBits(SettingsPort.dataBits)//DataBits
                && thisPort.setParity(SettingsPort.parity)
                && thisPort.setStopBits(SettingsPort.stopBits)
                && thisPort.setFlowControl(SettingsPort.flowControl))
        {
            if (thisPort.isOpen()){
                error_((SettingsPort.name+ " >> Open!"));
            }
        } else {
            thisPort.close();
            error_(thisPort.errorString().toLocal8Bit());
          }
    } else {
        thisPort.close();
        error_(thisPort.errorString().toLocal8Bit());
    }
}

void CRPI3Serial::handleError(QSerialPort::SerialPortError error)
{
    //проверка ошибок при работе
    if ( (thisPort.isOpen()) && (error == QSerialPort::ResourceError)) {
        error_(thisPort.errorString().toLocal8Bit());
        DisconnectPort();
    }
}

void CRPI3Serial::DisconnectPort()
{
    //Отключаем порт
    if(thisPort.isOpen()){
        thisPort.close();
        error_(SettingsPort.name + " Close!");
    }
}

void CRPI3Serial::WriteToPort(QByteArray data)
{
    //Запись данных в порт
    if(thisPort.isOpen()){
        thisPort.write(data);
        error_((SettingsPort.name+ " >> WriteData!"));
    }
}

void CRPI3Serial::ReadInPort()
{
    //Чтение данных из порта
    QByteArray data;
    data.append(thisPort.readAll());    
    outPort(data);
    error_((SettingsPort.name+ " >> ReadData!"));
    //((QString)(adr.toInt())).toLatin1().toHex()
}
