#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>
#include <QTime>
#include "../qtMainServer/globalcfg.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QSettings>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
//    enum MSG_CMD {
//        cmdAutchReq = 1,        // Сообщение успешного соединения ( на самом деле можно все это делать на сервере и не сообщать )
//        cmdServerParam,     // Сообщение о параметрах устройства
//        cmdMsgFromClient,   // Сообщение от клиента
//        cmdFileFromClient   // Файл от клиента
//        };

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void onSokConnected();      // Обработчик соеденения с сервером
    void onSokDisconnected();   // Обработчик отключения от сервера
    void onSokReadyRead();      // Обработчик получения данных с сервера
    void onSokDisplayError(QAbstractSocket::SocketError socketError);   // Обработчик ошибок

    void on_pbConnect_clicked();
    void on_pbDisconnect_clicked();


    void on_btnSendMessage_clicked();

    void on_btnSendFile_clicked();

    void on_pushButton_clicked();

    void on_bntGetParam_clicked();

    void on_btnSetParam_clicked();

    void closeEvent(QCloseEvent *event);

    void on_cbBaudRate_activated(const QString &arg1);

    void on_btnSearchCOMPorts_clicked();

    void on_cbStopBits_currentIndexChanged(int index);

    void on_cbFlowControl_currentIndexChanged(int index);

    void on_cbParity_currentIndexChanged(int index);

    void on_cbDataBits_currentIndexChanged(int index);

    void on_cbPortName_activated(const QString &arg1);

private:
    void LoadCfg();
    void SaveCfg();

    Ui::MainWindow *ui;

    QTcpSocket *_sok;
    quint16 _blockSize;
    QString _name;
    CSettingsDevice _settings;

    void AddToLog(QString text, QColor color = Qt::black);
};

#endif // MAINWINDOW_H
