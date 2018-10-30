#ifndef RPISERVER_H
#define RPISERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QByteArray>
#include <QDataStream>
#include "crpi3serial.h"

class CRpi3Server : public QTcpServer
{
    Q_OBJECT
public:
    enum MSG_CMD {
        cmdAutchReq = 1,    // Сообщение успешного соединения ( на самом деле можно все это делать на сервере и не сообщать )
        cmdServerParam,     // Сообщение содержит параметры устройства
        cmdMsgFromClient,   // Сообщение от клиента
        cmdFileFromClient   // Файл от клиента
        };

    explicit CRpi3Server(QObject *parent = 0, CRPI3Serial *device = 0);

    bool doStartServer(QHostAddress addr, qint16 port); // Запуск сервера
    bool doStopServer();
    void sendToClient(const QString& str);

signals:
    //void addLogToGui(QString string, QColor color = Qt::black);
    void SendDataToDevice(QByteArray data);

public slots:
    void onConnection();
    void onReadyRead(); // обработчик входящих данных
    void stateChanged(QAbstractSocket::SocketState stat); // обработчик изменения состояния вещающего сокета (он нам важен, дабы у нас всегда был кто-то, кто будет вещать
    void GetDataFromDevice(QString data);

private:
    QTcpSocket  *_sok; // вещатель
    CRPI3Serial *_device;
    quint16 _blockSize;
};

#endif // RPISERVER_H
