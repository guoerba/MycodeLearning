#include "mousepressedmoverelease.h"
#include <QLabel>
#include <QVBoxLayout>

MousePressedMoveRelease::MousePressedMoveRelease(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    QLabel *label = new QLabel("鼠标按下/移动/释放");
    label->setFrameStyle(QFrame::Box);
    label->setFixedHeight(50);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("background-color: blue; color: white; font-size: 25px");

    layout->addWidget(label);
}
