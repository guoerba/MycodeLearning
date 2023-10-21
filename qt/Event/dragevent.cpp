#include "dragevent.h"
#include <QLabel>
#include <QVBoxLayout>


DragEvent::DragEvent(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    textEdit = new TextEditX(this);
    textEdit->setPlaceholderText("支持拖放事件");

    layout->addWidget(textEdit);
}
