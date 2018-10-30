#ifndef RPI3SERVER_H
#define RPI3SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QByteArray>
#include <QDataStream>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QSettings>
#include <QCoreApplication>

#include "globalcfg.h"


class CRpi3Server : public QTcpServer
{
    Q_OBJECT
public:
/*    enum MSG_CMD {
        cmdAutchReq = 1,    // Сообщение успешного соединения ( на самом деле можно все это делать на сервере и не сообщать )
        cmdGetDeviceParam,  // Запрос параметров устройства
        cmdSetDeviceParam,  // Установка параметров устройства
        cmdMsgFromClient,   // Сообщение содержит сообщение от клиента
        cmdFileFromClient   // Файл от клиента для передачи на устройство
        };
*/
    explicit CRpi3Server(QObject *parent = 0);
    ~CRpi3Server();

    bool doStartServer(QHostAddress addr, qint16 port); // Запуск сервера
    bool doStopServer();    // Остановка сервера
    void SendMessageToClient(quint8 command, const QString& str);  // Отправка сообщения клиенту

signals:
    void SendDataToDevice(QByteArray data); // Отправляем данные на устройство

public slots:
    /* СЕРВЕР */
    void onConnection();
    void onReadyRead(); // обработчик входящих данных
    void stateChanged(QAbstractSocket::SocketState stat); // обработчик изменения состояния вещающего сокета (он нам важен, дабы у нас всегда был кто-то, кто будет вещать

    /* УСТРОЙСТВО */
    void GetDataFromDevice();
    bool SetCfgDevice(CSettingsDevice &cfg);
//    CSettingsDevice& GetCfgDevice();
    void onDeviceError(QSerialPort::SerialPortError error);
//    void SendDataToDevice(QString data);

private:
    void SaveCFG();
    void LoadCFG();

    /* СЕРВЕР */
    QTcpSocket  *_sok;   // Вещатель
    QHostAddress _addr;
    qint16 _port;
    quint16 _blockSize;

    /* УСТРОЙСТВО */
    QSerialPort     _device;        // Устройство
    CSettingsDevice  _cfgDevice;    // Параметры
};

#endif // RPISERVER_H
