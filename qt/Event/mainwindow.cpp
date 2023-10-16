#include "mainwindow.h"
#include <QHBoxLayout>
#include <QPushButton>
#include "mouseenterleave.h"
#include "mousepressedmoverelease.h"
#include "keyevent.h"
#include "timerevent.h"
#include "dragevent.h"
#include "paintevent.h"
#include "rightclickedevent.h"
#include "summarize.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    rightWidget = new QStackedWidget;

    QVBoxLayout *leftLayout = SetButtonLayout();
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addLayout(leftLayout);
    layout->addWidget(rightWidget);

    QWidget *mainwin = new QWidget;
    mainwin->setLayout(layout);
    this->setCentralWidget(mainwin);
    SetRightWidget();
}

MainWindow::~MainWindow()
{
}

QVBoxLayout* MainWindow::SetButtonLayout()
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    btnGroup = new QButtonGroup(this);
    QStringList s = {"鼠标进入/离开", "鼠标按下/移动/释放", "键盘事件",
                     "定时器事件", "拖动事件", "绘图事件", "右键菜单",
                     "总结：事件的传递流程"};

    for (int i = 0; i < s.size(); i++) {
        auto *btn = new QPushButton;
        btn->setText(QString("%1.%2").arg(i + 1).arg(s.at(i)));
        btn->setStyleSheet(R"(
                QPushButton {
                    font: 25px;
                    text-align: left;不
                }
            )");
        btn->setCheckable(true);
        btnGroup->addButton(btn, i);
        layout->addWidget(btn);
        connect(btn, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    }
    return layout;
}

void MainWindow::SetRightWidget()
{
    rightWidget->addWidget(new MouseEnterLeave);
    rightWidget->addWidget(new MousePressedMoveRelease);
    rightWidget->addWidget(new KeyEvent);
    rightWidget->addWidget(new TimerEvent);
    rightWidget->addWidget(new DragEvent);
    rightWidget->addWidget(new PaintEvent);
    rightWidget->addWidget(new RightClickedEvent);
    rightWidget->addWidget(new Summarize);
}

void MainWindow::onButtonClicked()
{
    rightWidget->setCurrentIndex(btnGroup->checkedId());
}
