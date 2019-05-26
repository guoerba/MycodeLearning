#pragma once

#include <QtWidgets/QMainWindow>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qgridlayout.h>
#include <qlabel.h>
#include <QtNetwork/qudpsocket.h>
#include <stdlib.h>
#include <chrono>
#include <ctime>


class UdpSender : public QMainWindow
{
	Q_OBJECT

public:
	UdpSender(QWidget *parent = Q_NULLPTR);

private:
	QLineEdit *portLineEdit, *dataLineEdit;
	QPushButton *sendBtn;
	QUdpSocket *s;
};
