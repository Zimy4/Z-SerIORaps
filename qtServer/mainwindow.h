#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QThread>
#include "crpi3serial.h"
#include "rpiserver.h"
#include "myserver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void savesettings(QString name, int baudrate, int DataBits, int Parity, int StopBits, int FlowControl);
    void writeData(QByteArray data);

private slots:
    void on_btnStartServer_clicked();
    void on_btnStopServer_clicked();

    void on_cbBaudRate_currentIndexChanged(int index);
    //////////////////////////////////
    void PrintCOMMessage(QString data);

    void on_btnSearchCOMPorts_clicked();

    void on_btnSaveCOMSettings_clicked();


    void on_btnTest_clicked();

private:
    Ui::MainWindow *ui;
    //CRPI3Serial Serial;
    CRPI3Serial ComPort;
    CRpi3Server *TCPTest;
    MyServer *_serv;
};

#endif // MAINWINDOW_H
