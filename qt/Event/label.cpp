#include "label.h"

Label::Label()
{

}

void Label::enterEvent(QEvent *event)
{
    this->setText(QString("enter event:%1").arg(count++));
}

void Label::leaveEvent(QEvent *event)
{
    this->setText(QString("leave event:%1").arg(count++));
}
