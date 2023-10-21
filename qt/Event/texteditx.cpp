#include "texteditx.h"
#include <QDebug>
#include <QMimeData>
#include <QUrl>
#include <QApplication>

TextEditX::TextEditX(QWidget *parent)
    : QTextEdit{parent}
{

}

void TextEditX::dragEnterEvent(QDragEnterEvent *e)
{
    qDebug() << "dragEnterEvent";
    //加上这句话才可以支持接下来的三个拖放事件
    e->acceptProposedAction();
}

void TextEditX::dragMoveEvent(QDragMoveEvent *e)
{
    qDebug() << "dragMoveEvent";
}

void TextEditX::dragLeaveEvent(QDragLeaveEvent *e)
{
    qDebug() << "dragLeaveEvent";
}

void TextEditX::dropEvent(QDropEvent *e)
{
    qDebug() << "dropEvent";

    QList<QUrl> urls = e->mimeData()->urls();
    if (urls.isEmpty()) {
        qDebug() << "文件名为空";
    } else {
        QString filename = urls.first().toLocalFile();
        QFile file(filename);
        if (file.open(QIODevice::ReadOnly)) {
            setPlainText(file.readAll());
        } else {
            qDebug() << QString("filename %1 cannot open").arg(filename);
        }
    }
}

void TextEditX::wheelEvent(QWheelEvent *e)
{
    //按下ctrl键
    if (QApplication::keyboardModifiers() == Qt::ControlModifier) {
        if (e->delta() > 0) {
            //滚轮远离使用者，进行放大
            this->zoomIn();
        } else {
            //滚轮靠近使用者，进行缩小
            this->zoomOut();
        }
    } else {
        //调用父类的实现，否则无法实现文本的上下滚动
        QTextEdit::wheelEvent(e);
    }
}
