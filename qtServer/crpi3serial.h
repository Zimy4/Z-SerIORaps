#ifndef CRPI3SERIAL_H
#define CRPI3SERIAL_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

struct Settings {//Структура с настройками порта
    QString name;
    qint32 baudRate;
    QSerialPort::DataBits dataBits;
    QSerialPort::Parity parity;
    QSerialPort::StopBits stopBits;
    QSerialPort::FlowControl flowControl;
};

class CRPI3Serial : public QObject
{
    Q_OBJECT

public:
    explicit CRPI3Serial(QObject *parent = 0);
    ~CRPI3Serial();
    QSerialPort thisPort;
    Settings SettingsPort;

signals:
    void finished_Port(); //Сигнал закрытия класса
    void error_(QString err);//Сигнал ошибок порта
    void outPort(QString data); //Сигнал вывода полученных данных

public slots:
    void ConnectPort(void); // Слот подключения порта
    void DisconnectPort(); // Слот отключения порта
    void Write_Settings_Port(QString name, int baudrate, int DataBits, int Parity, int StopBits, int FlowControl);// Слот занесение настроек порта в класс
    void process_Port(); //Тело
    void WriteToPort(QByteArray data); // Слот от правки данных в порт
    void ReadInPort(); //Слот чтения из порта по ReadyRead

private slots:
    void handleError(QSerialPort::SerialPortError error);//Слот обработки ощибок


};

#endif // CRPI3SERIAL_H
