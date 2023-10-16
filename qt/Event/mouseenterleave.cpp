#include "mouseenterleave.h"
#include <QLabel>
#include <QVBoxLayout>
#include "label.h"

MouseEnterLeave::MouseEnterLeave(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    Label *label = new Label();
    label->setFrameStyle(QFrame::Box);
    label->setFixedHeight(50);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("background-color: blue; color: white; font-size: 25px");

    downLabel = new Label();
    downLabel->setFrameStyle(QFrame::Box);
    downLabel->setFixedHeight(50);
    downLabel->setAlignment(Qt::AlignCenter);
    downLabel->setStyleSheet("background-color: red; color: white; font-size: 25px");

    layout->addWidget(label);
    layout->addWidget(downLabel);
    downLabel->installEventFilter(this);
}

bool MouseEnterLeave::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == downLabel) {
        if (event->type() == QEvent::Enter) {
            downLabel->setText(QString("enter event: %1").arg(count++));
        } else if (event->type() == QEvent::Leave) {
            downLabel->setText(QString("leave event: %1").arg(count++));
        }
    }

    return QWidget::eventFilter(watched, event);
}
