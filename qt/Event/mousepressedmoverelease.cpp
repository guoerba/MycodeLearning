#include "mousepressedmoverelease.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include "label.h"

MousePressedMoveRelease::MousePressedMoveRelease(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    mwin = new QWidget;

    Label *label = new Label();
    label->setFrameStyle(QFrame::Box);
    label->setFixedHeight(50);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("background-color: blue; color: white; font-size: 25px");

    mlabel = new QLabel(mwin);
    mlabel->setFrameStyle(QFrame::Box);
    mlabel->setFixedSize(100, 100);
    mlabel->setAlignment(Qt::AlignCenter);
    mlabel->setStyleSheet("background-color: red; color: white; font-size: 25px");

    layout->addWidget(label);
    layout->addWidget(mwin);

    mlabel->installEventFilter(this);
}

bool MousePressedMoveRelease::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == mlabel) {
        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *e = static_cast<QMouseEvent*>(event);
            labelPoint = mlabel->pos();
            mousePoint = e->globalPos();
            mlabel->setText(QString("(%1,%2)").arg(mlabel->pos().x()).arg(mlabel->pos().y()));
        } else if (event->type() == QEvent::MouseMove) {
            QMouseEvent *e = static_cast<QMouseEvent*>(event);
            QPoint dstPos = e->globalPos() - mousePoint + labelPoint;
            mlabel->move(dstPos);

            //左边界
            if (mlabel->pos().x() < 0) {
                mlabel->move(0, dstPos.y());
            }
            if (mlabel->pos().x() > mwin->width() - mlabel->width()) {
                mlabel->move(mwin->width() - mlabel->width(), dstPos.y());
            }
            if (mlabel->pos().y() < 0) {
                mlabel->move(dstPos.x(), 0);
                if (mlabel->pos().x() < 0) {
                    mlabel->move(0, 0);
                }
                if (mlabel->pos().x() > mwin->width() - mlabel->width()) {
                    mlabel->move(mwin->width() - mlabel->width(), 0);
                }
            }
            if (mlabel->pos().y() > mwin->height() - mlabel->height()) {
                mlabel->move(dstPos.x(), mwin->height() - mlabel->height());
                if (mlabel->pos().x() < 0) {
                    mlabel->move(0, mwin->height() - mlabel->height());
                }
                if (mlabel->pos().x() > mwin->width() - mlabel->width()) {
                    mlabel->move(mwin->width() - mlabel->width(), mwin->height() - mlabel->height());
                }
            }
            mlabel->setText(QString("(%1,%2)").arg(mlabel->pos().x()).arg(mlabel->pos().y()));
        } else if (event->type() == QEvent::MouseButtonRelease) {
            mlabel->setText("");
        }

    }

    return QWidget::eventFilter(watched, event);
}
