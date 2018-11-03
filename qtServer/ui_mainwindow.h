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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
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
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayoutCOM;
    QFormLayout *formLayout_2;
    QLabel *label;
    QSpinBox *sbNumServerPort;
    QLabel *label_2;
    QLineEdit *edtStatusServer;
    QVBoxLayout *verticalLayout;
    QPushButton *btnStartServer;
    QPushButton *btnStopServer;
    QPushButton *btnTest;
    QListWidget *lbServerLog;
    QVBoxLayout *verticalLayoutServer;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnSearchCOMPorts;
    QComboBox *cbPortName;
    QGridLayout *gridLayout;
    QLabel *lBR;
    QComboBox *cbStopBits;
    QComboBox *cbParity;
    QComboBox *cbDataBits;
    QComboBox *cbBaudRate;
    QComboBox *cbFlowControl;
    QLabel *lDB;
    QLabel *lP;
    QLabel *lSB;
    QLabel *lFC;
    QVBoxLayout *verticalLayout_2;
    QPushButton *btnSaveCOMSettings;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnConnectCOM;
    QPushButton *btnDisconectCOM;
    QListWidget *lbComLog;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(713, 502);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 711, 441));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayoutCOM = new QVBoxLayout();
        verticalLayoutCOM->setSpacing(6);
        verticalLayoutCOM->setObjectName(QStringLiteral("verticalLayoutCOM"));
        formLayout_2 = new QFormLayout();
        formLayout_2->setSpacing(6);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label);

        sbNumServerPort = new QSpinBox(horizontalLayoutWidget);
        sbNumServerPort->setObjectName(QStringLiteral("sbNumServerPort"));
        sbNumServerPort->setMaximum(65535);
        sbNumServerPort->setValue(8080);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, sbNumServerPort);

        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_2);

        edtStatusServer = new QLineEdit(horizontalLayoutWidget);
        edtStatusServer->setObjectName(QStringLiteral("edtStatusServer"));
        edtStatusServer->setReadOnly(true);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, edtStatusServer);


        verticalLayoutCOM->addLayout(formLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        btnStartServer = new QPushButton(horizontalLayoutWidget);
        btnStartServer->setObjectName(QStringLiteral("btnStartServer"));

        verticalLayout->addWidget(btnStartServer);

        btnStopServer = new QPushButton(horizontalLayoutWidget);
        btnStopServer->setObjectName(QStringLiteral("btnStopServer"));
        btnStopServer->setEnabled(false);

        verticalLayout->addWidget(btnStopServer);

        btnTest = new QPushButton(horizontalLayoutWidget);
        btnTest->setObjectName(QStringLiteral("btnTest"));

        verticalLayout->addWidget(btnTest);


        verticalLayoutCOM->addLayout(verticalLayout);

        lbServerLog = new QListWidget(horizontalLayoutWidget);
        lbServerLog->setObjectName(QStringLiteral("lbServerLog"));

        verticalLayoutCOM->addWidget(lbServerLog, 0, Qt::AlignBottom);


        horizontalLayout->addLayout(verticalLayoutCOM);

        verticalLayoutServer = new QVBoxLayout();
        verticalLayoutServer->setSpacing(6);
        verticalLayoutServer->setObjectName(QStringLiteral("verticalLayoutServer"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        btnSearchCOMPorts = new QPushButton(horizontalLayoutWidget);
        btnSearchCOMPorts->setObjectName(QStringLiteral("btnSearchCOMPorts"));

        horizontalLayout_2->addWidget(btnSearchCOMPorts);

        cbPortName = new QComboBox(horizontalLayoutWidget);
        cbPortName->setObjectName(QStringLiteral("cbPortName"));

        horizontalLayout_2->addWidget(cbPortName);


        verticalLayoutServer->addLayout(horizontalLayout_2);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lBR = new QLabel(horizontalLayoutWidget);
        lBR->setObjectName(QStringLiteral("lBR"));

        gridLayout->addWidget(lBR, 0, 0, 1, 1);

        cbStopBits = new QComboBox(horizontalLayoutWidget);
        cbStopBits->setObjectName(QStringLiteral("cbStopBits"));
        cbStopBits->setEnabled(true);

        gridLayout->addWidget(cbStopBits, 3, 1, 1, 1);

        cbParity = new QComboBox(horizontalLayoutWidget);
        cbParity->setObjectName(QStringLiteral("cbParity"));
        cbParity->setEnabled(true);

        gridLayout->addWidget(cbParity, 2, 1, 1, 1);

        cbDataBits = new QComboBox(horizontalLayoutWidget);
        cbDataBits->setObjectName(QStringLiteral("cbDataBits"));
        cbDataBits->setEnabled(true);

        gridLayout->addWidget(cbDataBits, 1, 1, 1, 1);

        cbBaudRate = new QComboBox(horizontalLayoutWidget);
        cbBaudRate->setObjectName(QStringLiteral("cbBaudRate"));
        cbBaudRate->setEnabled(true);

        gridLayout->addWidget(cbBaudRate, 0, 1, 1, 1);

        cbFlowControl = new QComboBox(horizontalLayoutWidget);
        cbFlowControl->setObjectName(QStringLiteral("cbFlowControl"));
        cbFlowControl->setEnabled(true);

        gridLayout->addWidget(cbFlowControl, 4, 1, 1, 1);

        lDB = new QLabel(horizontalLayoutWidget);
        lDB->setObjectName(QStringLiteral("lDB"));

        gridLayout->addWidget(lDB, 1, 0, 1, 1);

        lP = new QLabel(horizontalLayoutWidget);
        lP->setObjectName(QStringLiteral("lP"));

        gridLayout->addWidget(lP, 2, 0, 1, 1);

        lSB = new QLabel(horizontalLayoutWidget);
        lSB->setObjectName(QStringLiteral("lSB"));

        gridLayout->addWidget(lSB, 3, 0, 1, 1);

        lFC = new QLabel(horizontalLayoutWidget);
        lFC->setObjectName(QStringLiteral("lFC"));

        gridLayout->addWidget(lFC, 4, 0, 1, 1);


        verticalLayoutServer->addLayout(gridLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        btnSaveCOMSettings = new QPushButton(horizontalLayoutWidget);
        btnSaveCOMSettings->setObjectName(QStringLiteral("btnSaveCOMSettings"));

        verticalLayout_2->addWidget(btnSaveCOMSettings);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        btnConnectCOM = new QPushButton(horizontalLayoutWidget);
        btnConnectCOM->setObjectName(QStringLiteral("btnConnectCOM"));
        btnConnectCOM->setEnabled(true);

        horizontalLayout_3->addWidget(btnConnectCOM);

        btnDisconectCOM = new QPushButton(horizontalLayoutWidget);
        btnDisconectCOM->setObjectName(QStringLiteral("btnDisconectCOM"));
        btnDisconectCOM->setEnabled(true);

        horizontalLayout_3->addWidget(btnDisconectCOM);


        verticalLayout_2->addLayout(horizontalLayout_3);


        verticalLayoutServer->addLayout(verticalLayout_2);

        lbComLog = new QListWidget(horizontalLayoutWidget);
        lbComLog->setObjectName(QStringLiteral("lbComLog"));

        verticalLayoutServer->addWidget(lbComLog, 0, Qt::AlignBottom);


        horizontalLayout->addLayout(verticalLayoutServer);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 713, 21));
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
        label_2->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\201\321\202\320\276\321\217\320\275\320\270\320\265:", 0));
        btnStartServer->setText(QApplication::translate("MainWindow", "Start Server", 0));
        btnStopServer->setText(QApplication::translate("MainWindow", "Stop Server", 0));
        btnTest->setText(QApplication::translate("MainWindow", "TestData", 0));
        btnSearchCOMPorts->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\270\321\201\320\272", 0));
        lBR->setText(QApplication::translate("MainWindow", "BaudRate:", 0));
        lDB->setText(QApplication::translate("MainWindow", "Data bits:", 0));
        lP->setText(QApplication::translate("MainWindow", "Parity:", 0));
        lSB->setText(QApplication::translate("MainWindow", "Stop bits:", 0));
        lFC->setText(QApplication::translate("MainWindow", "Flow control:", 0));
        btnSaveCOMSettings->setText(QApplication::translate("MainWindow", "Save Settings", 0));
        btnConnectCOM->setText(QApplication::translate("MainWindow", "Conect", 0));
        btnDisconectCOM->setText(QApplication::translate("MainWindow", "Disconect", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
