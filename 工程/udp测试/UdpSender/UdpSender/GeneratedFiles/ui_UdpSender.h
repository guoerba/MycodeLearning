/********************************************************************************
** Form generated from reading UI file 'UdpSender.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UDPSENDER_H
#define UI_UDPSENDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UdpSenderClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *UdpSenderClass)
    {
        if (UdpSenderClass->objectName().isEmpty())
            UdpSenderClass->setObjectName(QString::fromUtf8("UdpSenderClass"));
        UdpSenderClass->resize(600, 400);
        menuBar = new QMenuBar(UdpSenderClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        UdpSenderClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(UdpSenderClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        UdpSenderClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(UdpSenderClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        UdpSenderClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(UdpSenderClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        UdpSenderClass->setStatusBar(statusBar);

        retranslateUi(UdpSenderClass);

        QMetaObject::connectSlotsByName(UdpSenderClass);
    } // setupUi

    void retranslateUi(QMainWindow *UdpSenderClass)
    {
        UdpSenderClass->setWindowTitle(QApplication::translate("UdpSenderClass", "UdpSender", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UdpSenderClass: public Ui_UdpSenderClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UDPSENDER_H
