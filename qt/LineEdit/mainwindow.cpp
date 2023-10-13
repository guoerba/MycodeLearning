#include "mainwindow.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QMessageBox>
#include <QValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    btnGroup1NormalMode = new QPushButton("正常模式");
    btnGroup1PasswordMode = new QPushButton("密码模式");
    btnGroup1NoDisplayBackMode = new QPushButton("无回显");
    btnGroup1Password2Mode = new QPushButton("失去焦点变密码模式");
    btnGroup1Output = new QPushButton("输出内容");
    lineGroup1 = new QLineEdit;
    lineGroup1->setPlaceholderText("密码");

    btnGroup2LeftAlign = new QPushButton("左对齐");
    btnGroup2MiddleAlign = new QPushButton("居中对齐");
    btnGroup2RightAlign = new QPushButton("右对齐");
    lineGroup2 = new QLineEdit;

    btnGroup3WriteRead = new QPushButton("可读可写");
    btnGroup3ReadOnly = new QPushButton("只读");
    btnGroup3Disable = new QPushButton("禁能");
    btnGroup3Enable = new QPushButton("使能");
    btnGroup3Output = new QPushButton("输出内容");
    lineGroup3 = new QLineEdit;

    btnGroup4NoControl = new QPushButton("无控制");
    btnGroup4PhoneNumber = new QPushButton("手机号码");
    btnGroup4Password = new QPushButton("密钥");
    lineGroup4 = new QLineEdit;

    lineGroup5textChanged_1 = new QLineEdit;
    lineGroup5textChanged_1->setValidator(new QIntValidator(this));
    lineGroup5textChanged_2 = new QLineEdit;
    lineGroup5textChanged_2->setValidator(new QIntValidator(this));
    lineGroup5textChanged_3 = new QLineEdit;
    lineGroup5textChanged_3->setReadOnly(true);
    lineGroup5editingFinished_1 = new QLineEdit;
    lineGroup5editingFinished_1->setValidator(new QIntValidator(this));
    lineGroup5editingFinished_2 = new QLineEdit;
    lineGroup5editingFinished_2->setValidator(new QIntValidator(this));
    lineGroup5editingFinished_3 = new QLineEdit;
    lineGroup5editingFinished_3->setReadOnly(true);

    QGridLayout *layoutGroup1 = new QGridLayout;
    layoutGroup1->addWidget(lineGroup1, 0, 0, 1, 4);
    layoutGroup1->addWidget(btnGroup1Output, 0, 4);
    layoutGroup1->addWidget(btnGroup1NormalMode, 1, 0);
    layoutGroup1->addWidget(btnGroup1PasswordMode, 1, 1);
    layoutGroup1->addWidget(btnGroup1NoDisplayBackMode, 1, 2);
    layoutGroup1->addWidget(btnGroup1Password2Mode, 1, 3, 1, 2);

    QGridLayout *layoutGroup2 = new QGridLayout;
    layoutGroup2->addWidget(lineGroup2, 0, 0, 1, 3);
    layoutGroup2->addWidget(btnGroup2LeftAlign, 1, 0);
    layoutGroup2->addWidget(btnGroup2MiddleAlign, 1, 1);
    layoutGroup2->addWidget(btnGroup2RightAlign, 1, 2);

    QGridLayout *layoutGroup3 = new QGridLayout;
    layoutGroup3->addWidget(lineGroup3, 0, 0, 1, 3);
    layoutGroup3->addWidget(btnGroup3Output, 0, 3);
    layoutGroup3->addWidget(btnGroup3WriteRead, 1, 0);
    layoutGroup3->addWidget(btnGroup3ReadOnly, 1, 1);
    layoutGroup3->addWidget(btnGroup3Disable, 1, 2);
    layoutGroup3->addWidget(btnGroup3Enable, 1, 3);

    QGridLayout *layoutGroup4 = new QGridLayout;
    layoutGroup4->addWidget(lineGroup4, 0, 0, 1, 3);
    layoutGroup4->addWidget(btnGroup4NoControl, 1, 0);
    layoutGroup4->addWidget(btnGroup4PhoneNumber, 1, 1);
    layoutGroup4->addWidget(btnGroup4Password, 1, 2);

    QGridLayout *layoutGroup5 = new QGridLayout;
    layoutGroup5->addWidget(new QLabel("textChanged信号："), 0, 0);
    layoutGroup5->addWidget(lineGroup5textChanged_1, 0, 1);
    layoutGroup5->addWidget(new QLabel("+"), 0, 2);
    layoutGroup5->addWidget(lineGroup5textChanged_2, 0, 3);
    layoutGroup5->addWidget(new QLabel("="), 0, 4);
    layoutGroup5->addWidget(lineGroup5textChanged_3, 0, 5);
    layoutGroup5->addWidget(new QLabel("editingFinished信号："), 1, 0);
    layoutGroup5->addWidget(lineGroup5editingFinished_1, 1, 1);
    layoutGroup5->addWidget(new QLabel("+"), 1, 2);
    layoutGroup5->addWidget(lineGroup5editingFinished_2, 1, 3);
    layoutGroup5->addWidget(new QLabel("="), 1, 4);
    layoutGroup5->addWidget(lineGroup5editingFinished_3, 1, 5);

    QGroupBox *group1 = new QGroupBox("回显模式");
    group1->setLayout(layoutGroup1);
    QGroupBox *group2 = new QGroupBox("对齐方式");
    group2->setLayout(layoutGroup2);
    QGroupBox *group3 = new QGroupBox("读写控制");
    group3->setLayout(layoutGroup3);
    QGroupBox *group4 = new QGroupBox("各式控制");
    group4->setLayout(layoutGroup4);
    QGroupBox *group5 = new QGroupBox("信号槽");
    group5->setLayout(layoutGroup5);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(group1);
    layout->addWidget(group2);
    layout->addWidget(group3);
    layout->addWidget(group4);
    layout->addWidget(group5);

    QWidget *mainwin = new QWidget(this);
    mainwin->setLayout(layout);

    this->setCentralWidget(mainwin);

    connect(btnGroup1NormalMode, &QPushButton::clicked, this, [=](){
        lineGroup1->setPlaceholderText("正常模式");
        lineGroup1->setEchoMode(QLineEdit::Normal);});
    connect(btnGroup1PasswordMode, &QPushButton::clicked, this, [=](){
        lineGroup1->setPlaceholderText("密码模式");
        lineGroup1->setEchoMode(QLineEdit::Password);});
    connect(btnGroup1NoDisplayBackMode, &QPushButton::clicked, this, [=](){
        lineGroup1->setPlaceholderText("无回显");
        lineGroup1->setEchoMode(QLineEdit::NoEcho);});
    connect(btnGroup1Password2Mode, &QPushButton::clicked, this, [=](){
        lineGroup1->setPlaceholderText("失去焦点变密码模式");
        lineGroup1->setEchoMode(QLineEdit::PasswordEchoOnEdit);});
    connect(btnGroup1Output, &QPushButton::clicked, this, [=](){
        QMessageBox::information(this, "输出内容", lineGroup1->text());
    });

    connect(btnGroup2LeftAlign, &QPushButton::clicked, this, [=](){
        lineGroup2->setPlaceholderText("左对齐");
        lineGroup2->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    });
    connect(btnGroup2MiddleAlign, &QPushButton::clicked, this, [=](){
        lineGroup2->setPlaceholderText("居中对齐");
        lineGroup2->setAlignment(Qt::AlignCenter);
    });
    connect(btnGroup2RightAlign, &QPushButton::clicked, this, [=](){
        lineGroup2->setPlaceholderText("右对齐");
        lineGroup2->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    });

    connect(btnGroup3WriteRead, &QPushButton::clicked, this, [=](){
        lineGroup3->setPlaceholderText("可读可写");
        lineGroup3->setReadOnly(false);
    });
    connect(btnGroup3ReadOnly, &QPushButton::clicked, this, [=](){
        lineGroup3->setPlaceholderText("只读");
        lineGroup3->setReadOnly(true);
    });
    connect(btnGroup3Disable, &QPushButton::clicked, this, [=](){
        lineGroup3->setPlaceholderText("禁能");
        lineGroup3->setEnabled(false);
    });
    connect(btnGroup3Enable, &QPushButton::clicked, this, [=](){
        lineGroup3->setPlaceholderText("使能");
        lineGroup3->setEnabled(true);
    });
    connect(btnGroup3Output, &QPushButton::clicked, this, [=](){
        QMessageBox::information(this, "输出内容", lineGroup3->text());
    });

    connect(btnGroup4NoControl, &QPushButton::clicked, this, [=](){
        lineGroup4->setPlaceholderText("无限制");
        lineGroup4->setInputMask("");
    });
    connect(btnGroup4PhoneNumber, &QPushButton::clicked, this, [=](){
        lineGroup4->setPlaceholderText("电话号码");
        lineGroup4->setInputMask("99999999999;_");
    });
    connect(btnGroup4Password, &QPushButton::clicked, this, [=](){
        lineGroup4->setPlaceholderText("序列号");
        lineGroup4->setInputMask(">AAAAA-AAAAA-AAAAA-AAAAA-AAAAA;#");
    });

    connect(lineGroup5textChanged_1, &QLineEdit::textChanged, this, &MainWindow::lineGroup5textChangedSlot);
    connect(lineGroup5textChanged_2, &QLineEdit::textChanged, this, &MainWindow::lineGroup5textChangedSlot);
    connect(lineGroup5editingFinished_1, &QLineEdit::editingFinished, this, &MainWindow::lineGroup5EditingFinishedSlot);
    connect(lineGroup5editingFinished_2, &QLineEdit::editingFinished, this, &MainWindow::lineGroup5EditingFinishedSlot);
}

MainWindow::~MainWindow()
{
}

void MainWindow::lineGroup5textChangedSlot(const QString &text)
{
    int sum = lineGroup5textChanged_1->text().toInt() + lineGroup5textChanged_2->text().toInt();
    lineGroup5textChanged_3->setText(QString::number(sum));
}

void MainWindow::lineGroup5EditingFinishedSlot()
{
    int sum = lineGroup5editingFinished_1->text().toInt() + lineGroup5editingFinished_2->text().toInt();
    lineGroup5editingFinished_3->setText(QString::number(sum));
}

