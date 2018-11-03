/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayoutCOM;
    QFormLayout *formLayout_2;
    QLabel *label;
    QSpinBox *sbNumServerPort;
    QLabel *lbListDevice;
    QComboBox *cbListDevices;
    QVBoxLayout *verticalLayout;
    QPushButton *btnStartServer;
    QPushButton *btnStopServer;
    QPushButton *btnTest;
    QListWidget *lbServerLog;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(630, 456);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 621, 391));
        verticalLayoutCOM = new QVBoxLayout(layoutWidget);
        verticalLayoutCOM->setSpacing(6);
        verticalLayoutCOM->setContentsMargins(11, 11, 11, 11);
        verticalLayoutCOM->setObjectName(QStringLiteral("verticalLayoutCOM"));
        verticalLayoutCOM->setContentsMargins(0, 0, 0, 0);
        formLayout_2 = new QFormLayout();
        formLayout_2->setSpacing(6);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label);

        sbNumServerPort = new QSpinBox(layoutWidget);
        sbNumServerPort->setObjectName(QStringLiteral("sbNumServerPort"));
        sbNumServerPort->setMaximum(65535);
        sbNumServerPort->setValue(8080);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, sbNumServerPort);

        lbListDevice = new QLabel(layoutWidget);
        lbListDevice->setObjectName(QStringLiteral("lbListDevice"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, lbListDevice);

        cbListDevices = new QComboBox(layoutWidget);
        cbListDevices->setObjectName(QStringLiteral("cbListDevices"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, cbListDevices);


        verticalLayoutCOM->addLayout(formLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        btnStartServer = new QPushButton(layoutWidget);
        btnStartServer->setObjectName(QStringLiteral("btnStartServer"));

        verticalLayout->addWidget(btnStartServer);

        btnStopServer = new QPushButton(layoutWidget);
        btnStopServer->setObjectName(QStringLiteral("btnStopServer"));
        btnStopServer->setEnabled(false);

        verticalLayout->addWidget(btnStopServer);

        btnTest = new QPushButton(layoutWidget);
        btnTest->setObjectName(QStringLiteral("btnTest"));
        btnTest->setEnabled(false);

        verticalLayout->addWidget(btnTest);


        verticalLayoutCOM->addLayout(verticalLayout);

        lbServerLog = new QListWidget(layoutWidget);
        lbServerLog->setObjectName(QStringLiteral("lbServerLog"));

        verticalLayoutCOM->addWidget(lbServerLog, 0, Qt::AlignBottom);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 630, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label->setText(QApplication::translate("MainWindow", "\320\237\320\276\321\200\321\202:", 0));
        lbListDevice->setText(QApplication::translate("MainWindow", "\320\243\321\201\321\202\321\200\320\276\320\271\321\201\321\202\320\262\320\276:", 0));
        btnStartServer->setText(QApplication::translate("MainWindow", "Start Server", 0));
        btnStopServer->setText(QApplication::translate("MainWindow", "Stop Server", 0));
        btnTest->setText(QApplication::translate("MainWindow", "TestData", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
