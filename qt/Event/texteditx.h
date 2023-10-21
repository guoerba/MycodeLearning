#ifndef TEXTEDITX_H
#define TEXTEDITX_H

#include <QTextEdit>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDragLeaveEvent>
#include <QDropEvent>
#include <QWheelEvent>

class TextEditX : public QTextEdit
{
    Q_OBJECT
public:
    explicit TextEditX(QWidget *parent = nullptr);

signals:
protected:
    void dragEnterEvent(QDragEnterEvent *e);
    void dragMoveEvent(QDragMoveEvent *e);
    void dragLeaveEvent(QDragLeaveEvent *e);
    void dropEvent(QDropEvent *e);
    void wheelEvent(QWheelEvent *e);
};

#endif // TEXTEDITX_H
