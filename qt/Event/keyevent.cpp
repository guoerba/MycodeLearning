#include "keyevent.h"
#include <QLabel>
#include <QVBoxLayout>

KeyEvent::KeyEvent(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    label = new QLabel();
    label->setFrameStyle(QFrame::Box);
    label->setFixedSize(100, 100);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("background-color: red; color: white; font-size: 25px");

    layout->addWidget(label);
    this->setFocusPolicy(Qt::StrongFocus);
}

void KeyEvent::keyPressEvent(QKeyEvent *event)
{
    QPoint mPos = label->pos();
    switch (event->key()) {
    case Qt::Key_Up:
        if (mPos.y() < - label->height()) {
            label->move(mPos.x(), this->height());
        } else {
            label->move(mPos.x(), mPos.y() - 10);
        }
        break;
    case Qt::Key_Down:
        if (mPos.y() > this->height()) {
            label->move(mPos.x(), 0 - label->height());
        } else {
            label->move(mPos.x(), mPos.y() + 10);
        }
        break;
    case Qt::Key_Left:
        if (mPos.x() < - label->width()) {
            label->move(this->width(), mPos.y());
        } else {
            label->move(mPos.x() - 10, mPos.y());
        }
        break;
    case Qt::Key_Right:
        if (mPos.x() > this->width()) {
            label->move(- label->width(), mPos.y());
        } else {
            label->move(mPos.x() + 10, mPos.y());
        }
        break;
    }
    label->setText(QString("(%1,%2)").arg(label->pos().x()).arg(label->pos().y()));
}
