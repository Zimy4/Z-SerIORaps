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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
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
    QVBoxLayout *verticalLayout;
    QLineEdit *leHost;
    QSpinBox *sbPort;
    QLineEdit *leName;
    QPushButton *pbConnect;
    QPushButton *pbDisconnect;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QListWidget *lwLog;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *leFileName;
    QProgressBar *pgFileSend;
    QPushButton *pushButton;
    QPushButton *btnSendFile;
    QSpacerItem *verticalSpacer;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_4;
    QLabel *label;
    QLineEdit *leMessage;
    QPushButton *btnSendMessage;
    QSpacerItem *verticalSpacer_2;
    QWidget *layoutWidget_2;
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
    QLabel *label_2;
    QCheckBox *chOpened;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *bntGetParam;
    QPushButton *btnSetParam;
    QListWidget *lbComLog;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(785, 376);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 131, 132));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        leHost = new QLineEdit(layoutWidget);
        leHost->setObjectName(QStringLiteral("leHost"));

        verticalLayout->addWidget(leHost);

        sbPort = new QSpinBox(layoutWidget);
        sbPort->setObjectName(QStringLiteral("sbPort"));
        sbPort->setMaximum(65536);
        sbPort->setValue(8080);

        verticalLayout->addWidget(sbPort);

        leName = new QLineEdit(layoutWidget);
        leName->setObjectName(QStringLiteral("leName"));

        verticalLayout->addWidget(leName);

        pbConnect = new QPushButton(layoutWidget);
        pbConnect->setObjectName(QStringLiteral("pbConnect"));

        verticalLayout->addWidget(pbConnect);

        pbDisconnect = new QPushButton(layoutWidget);
        pbDisconnect->setObjectName(QStringLiteral("pbDisconnect"));
        pbDisconnect->setEnabled(false);

        verticalLayout->addWidget(pbDisconnect);

        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 150, 491, 191));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        lwLog = new QListWidget(verticalLayoutWidget);
        lwLog->setObjectName(QStringLiteral("lwLog"));

        verticalLayout_2->addWidget(lwLog);

        verticalLayoutWidget_2 = new QWidget(centralWidget);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(340, 10, 161, 131));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        leFileName = new QLineEdit(verticalLayoutWidget_2);
        leFileName->setObjectName(QStringLiteral("leFileName"));
        leFileName->setReadOnly(true);

        verticalLayout_3->addWidget(leFileName);

        pgFileSend = new QProgressBar(verticalLayoutWidget_2);
        pgFileSend->setObjectName(QStringLiteral("pgFileSend"));
        pgFileSend->setValue(24);

        verticalLayout_3->addWidget(pgFileSend);

        pushButton = new QPushButton(verticalLayoutWidget_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout_3->addWidget(pushButton);

        btnSendFile = new QPushButton(verticalLayoutWidget_2);
        btnSendFile->setObjectName(QStringLiteral("btnSendFile"));
        btnSendFile->setEnabled(false);

        verticalLayout_3->addWidget(btnSendFile);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        verticalLayoutWidget_3 = new QWidget(centralWidget);
        verticalLayoutWidget_3->setObjectName(QStringLiteral("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(160, 10, 161, 131));
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget_3);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_4->addWidget(label);

        leMessage = new QLineEdit(verticalLayoutWidget_3);
        leMessage->setObjectName(QStringLiteral("leMessage"));

        verticalLayout_4->addWidget(leMessage);

        btnSendMessage = new QPushButton(verticalLayoutWidget_3);
        btnSendMessage->setObjectName(QStringLiteral("btnSendMessage"));
        btnSendMessage->setEnabled(false);

        verticalLayout_4->addWidget(btnSendMessage);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);

        layoutWidget_2 = new QWidget(centralWidget);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(510, 10, 258, 331));
        verticalLayoutServer = new QVBoxLayout(layoutWidget_2);
        verticalLayoutServer->setSpacing(6);
        verticalLayoutServer->setContentsMargins(11, 11, 11, 11);
        verticalLayoutServer->setObjectName(QStringLiteral("verticalLayoutServer"));
        verticalLayoutServer->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        btnSearchCOMPorts = new QPushButton(layoutWidget_2);
        btnSearchCOMPorts->setObjectName(QStringLiteral("btnSearchCOMPorts"));
        btnSearchCOMPorts->setEnabled(false);

        horizontalLayout_2->addWidget(btnSearchCOMPorts);

        cbPortName = new QComboBox(layoutWidget_2);
        cbPortName->setObjectName(QStringLiteral("cbPortName"));

        horizontalLayout_2->addWidget(cbPortName);


        verticalLayoutServer->addLayout(horizontalLayout_2);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lBR = new QLabel(layoutWidget_2);
        lBR->setObjectName(QStringLiteral("lBR"));

        gridLayout->addWidget(lBR, 0, 0, 1, 1);

        cbStopBits = new QComboBox(layoutWidget_2);
        cbStopBits->setObjectName(QStringLiteral("cbStopBits"));
        cbStopBits->setEnabled(true);

        gridLayout->addWidget(cbStopBits, 3, 1, 1, 1);

        cbParity = new QComboBox(layoutWidget_2);
        cbParity->setObjectName(QStringLiteral("cbParity"));
        cbParity->setEnabled(true);

        gridLayout->addWidget(cbParity, 2, 1, 1, 1);

        cbDataBits = new QComboBox(layoutWidget_2);
        cbDataBits->setObjectName(QStringLiteral("cbDataBits"));
        cbDataBits->setEnabled(true);

        gridLayout->addWidget(cbDataBits, 1, 1, 1, 1);

        cbBaudRate = new QComboBox(layoutWidget_2);
        cbBaudRate->setObjectName(QStringLiteral("cbBaudRate"));
        cbBaudRate->setEnabled(true);

        gridLayout->addWidget(cbBaudRate, 0, 1, 1, 1);

        cbFlowControl = new QComboBox(layoutWidget_2);
        cbFlowControl->setObjectName(QStringLiteral("cbFlowControl"));
        cbFlowControl->setEnabled(true);

        gridLayout->addWidget(cbFlowControl, 4, 1, 1, 1);

        lDB = new QLabel(layoutWidget_2);
        lDB->setObjectName(QStringLiteral("lDB"));

        gridLayout->addWidget(lDB, 1, 0, 1, 1);

        lP = new QLabel(layoutWidget_2);
        lP->setObjectName(QStringLiteral("lP"));

        gridLayout->addWidget(lP, 2, 0, 1, 1);

        lSB = new QLabel(layoutWidget_2);
        lSB->setObjectName(QStringLiteral("lSB"));

        gridLayout->addWidget(lSB, 3, 0, 1, 1);

        lFC = new QLabel(layoutWidget_2);
        lFC->setObjectName(QStringLiteral("lFC"));

        gridLayout->addWidget(lFC, 4, 0, 1, 1);

        label_2 = new QLabel(layoutWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 5, 0, 1, 1);

        chOpened = new QCheckBox(layoutWidget_2);
        chOpened->setObjectName(QStringLiteral("chOpened"));
        chOpened->setEnabled(false);
        chOpened->setCheckable(true);

        gridLayout->addWidget(chOpened, 5, 1, 1, 1);


        verticalLayoutServer->addLayout(gridLayout);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        bntGetParam = new QPushButton(layoutWidget_2);
        bntGetParam->setObjectName(QStringLiteral("bntGetParam"));
        bntGetParam->setEnabled(false);

        horizontalLayout_3->addWidget(bntGetParam);

        btnSetParam = new QPushButton(layoutWidget_2);
        btnSetParam->setObjectName(QStringLiteral("btnSetParam"));
        btnSetParam->setEnabled(false);

        horizontalLayout_3->addWidget(btnSetParam);


        verticalLayout_5->addLayout(horizontalLayout_3);


        verticalLayoutServer->addLayout(verticalLayout_5);

        lbComLog = new QListWidget(layoutWidget_2);
        lbComLog->setObjectName(QStringLiteral("lbComLog"));

        verticalLayoutServer->addWidget(lbComLog, 0, Qt::AlignBottom);

        MainWindow->setCentralWidget(centralWidget);
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
        leHost->setText(QApplication::translate("MainWindow", "127.0.0.1", 0));
        leName->setText(QApplication::translate("MainWindow", "MyName", 0));
        pbConnect->setText(QApplication::translate("MainWindow", "Connect", 0));
        pbDisconnect->setText(QApplication::translate("MainWindow", "Disconnect", 0));
        leFileName->setText(QApplication::translate("MainWindow", "FileName.txt", 0));
        pushButton->setText(QApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \321\204\320\260\320\271\320\273", 0));
        btnSendFile->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214 \321\204\320\260\320\271\320\273", 0));
        label->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214 \320\272\320\276\320\274\320\260\320\275\320\264\321\203(\321\202\320\265\320\272\321\201\321\202):", 0));
        btnSendMessage->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", 0));
        btnSearchCOMPorts->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\273\321\203\321\207\320\270\321\202\321\214 \321\201\320\277\320\270\321\201\320\276\320\272", 0));
        lBR->setText(QApplication::translate("MainWindow", "BaudRate:", 0));
        lDB->setText(QApplication::translate("MainWindow", "Data bits:", 0));
        lP->setText(QApplication::translate("MainWindow", "Parity:", 0));
        lSB->setText(QApplication::translate("MainWindow", "Stop bits:", 0));
        lFC->setText(QApplication::translate("MainWindow", "Flow control:", 0));
        label_2->setText(QApplication::translate("MainWindow", "Port open:", 0));
        chOpened->setText(QApplication::translate("MainWindow", "CheckBox", 0));
        bntGetParam->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\273\321\203\321\207\320\270\321\202\321\214", 0));
        btnSetParam->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
