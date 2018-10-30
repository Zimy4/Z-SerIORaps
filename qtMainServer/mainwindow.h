#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include "rpi3server.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onAddLogMessage(QString text, QColor color = Qt::black);

private slots:
    void closeEvent(QCloseEvent *event);

    void on_btnStartServer_clicked();

    void on_btnStopServer_clicked();

private:
    Ui::MainWindow *ui;
    CRpi3Server serv;
};

#endif // MAINWINDOW_H
