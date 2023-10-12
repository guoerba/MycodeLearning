#include "mainwindow.h"
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    btnStopandStart = new QPushButton(QIcon("://icon/pause2.jpg"), "停止");
    btnStopandStart->setIcon(QIcon("://icon/pause2.jpg"));
    btnConnect = new QPushButton("连接");
    btnSendCommand = new QPushButton("发送命令");
    btnSendCommand->setEnabled(false);
    btnStyleSheet = new QPushButton("一个按钮");
    btnSlotFunction = new QPushButton("信号演示");

    QHBoxLayout *layoutGroup1 = new QHBoxLayout;
    layoutGroup1->addWidget(btnStopandStart);
    QHBoxLayout *layoutGroup2 = new QHBoxLayout;
    layoutGroup2->addWidget(btnConnect);
    layoutGroup2->addWidget(btnSendCommand);
    QHBoxLayout *layoutGroup3 = new QHBoxLayout;
    layoutGroup3->addWidget(btnStyleSheet);
    QHBoxLayout *layoutGroup4 = new QHBoxLayout;
    layoutGroup4->addWidget(btnSlotFunction);

    QGroupBox *group1 = new QGroupBox("设置文本和图标");
    group1->setLayout(layoutGroup1);
    QGroupBox *group2 = new QGroupBox("使能禁能");
    group2->setLayout(layoutGroup2);
    QGroupBox *group3 = new QGroupBox("样式表");
    group3->setLayout(layoutGroup3);
    QGroupBox *group4 = new QGroupBox("槽函数");
    group4->setLayout(layoutGroup4);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(group1);
    layout->addWidget(group2);
    layout->addWidget(group3);
    layout->addWidget(group4);

    QWidget *mainwin = new QWidget;
    mainwin->setLayout(layout);
    this->setCentralWidget(mainwin);
    this->setMinimumSize(300, 300);
    this->setMaximumSize(600, 600);

    connect(btnStopandStart, &QPushButton::clicked, this, &MainWindow::btn_onclick_StopandStart);
    connect(btnConnect, &QPushButton::clicked, this, &MainWindow::btn_onclick_Connect);
    connect(btnStyleSheet, &QPushButton::clicked, this, &MainWindow::btn_onclick_StyleSheet);
    connect(btnSlotFunction, &QPushButton::clicked, this, &MainWindow::btn_onclick_SlotFunction);
    btnStopandStart->setIcon(QIcon());

    oldStyleSheet = btnStyleSheet->styleSheet();
}

MainWindow::~MainWindow()
{
}

void MainWindow::btn_onclick_StopandStart()
{
    QString s = btnStopandStart->text();
    if (s == "停止") {
        btnStopandStart->setText("启动");
        btnStopandStart->setIcon(QIcon("://icon/play.jpeg"));
    } else {
        btnStopandStart->setText("停止");
        btnStopandStart->setIcon(QIcon("://icon/pause2.jpg"));
    }
}
void MainWindow::btn_onclick_Connect()
{
    QString s = btnConnect->text();
    if (s == "连接") {
        btnConnect->setText("停止连接");
        btnSendCommand->setEnabled(true);
    } else {
        btnConnect->setText("连接");
        btnSendCommand->setEnabled(false);
    }
}
void MainWindow::btn_onclick_StyleSheet()
{
    if (styleSheetFlag == false) {
        btnStyleSheet->setStyleSheet("background-color: #00FF00;" //背景颜色
                          "color: #FF0000;"            //前景色
                          "color: rgb(255,0,0);"
                          "color: rgbd(255,0,0,0);"
                          "color: red;"
                          "margin: 10px;"              //边缘
                          "padding: 5px;"
                          "padding-left: 15px;"
                          "padding-right: 15px;"
                          "border-radius: 5px;"        //圆角边框
                          "border: 3px solid #abc;");
        styleSheetFlag = true;
    } else {
        btnStyleSheet->setStyleSheet(oldStyleSheet);
        qDebug() << btnStyleSheet->styleSheet();
        styleSheetFlag = false;
    }
}
void MainWindow::btn_onclick_SlotFunction()
{
    qDebug() << "success";
}
