#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QDebug>
#include "myclient.h"
class MyClient;

class MyServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit MyServer(QWidget *widget = 0, QObject *parent = 0);
    bool doStartServer(QHostAddress addr, qint16 port);
    void doSendToAllUserJoin(QString name); // Отправляем всем клиентам сообщение что присоеденился новый(name) клиент
    void doSendToAllUserLeft(QString name); // Отправляем всем клиентам сообщение что отсоеденился(name) клиент
    void doSendToAllMessage(QString message, QString fromUsername); // Отправляем всем сообщение от клиента(fromUsername)
    void doSendToAllServerMessage(QString message); // Отправляем всем клиентам сообщение от сервера
    void doSendServerMessageToUsers(QString message, const QStringList &users); // Отправляем выбранным клиентам сообщение от сервера
    void doSendMessageToUsers(QString message, const QStringList &users, QString fromUsername);
    QStringList getUsersOnline() const;
    bool isNameValid(QString name) const;
    bool isNameUsed(QString name) const;

signals:
    void addLogToGui(QString string, QColor color = Qt::black);

public slots:
    void onMessageFromGui(QString message, const QStringList &users);
    void onRemoveUser(MyClient *client);

protected:
    void incomingConnection(int handle);

private:
    QList<MyClient *> _clients;
    QWidget *_widget;

};

#endif // MYSERVER_H
