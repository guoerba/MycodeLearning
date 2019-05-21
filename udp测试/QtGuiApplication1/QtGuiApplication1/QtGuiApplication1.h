#pragma once

#include <QtWidgets/QMainWindow>
#include <qlineedit.h>
#include <qtextedit.h>
#include <qlabel.h>
#include <qgridlayout.h>
#include "UdpListener.h"
#include "UdpSender.h"

class MinWin : public QMainWindow
{
	Q_OBJECT;

public:
	MinWin(QWidget *parent = Q_NULLPTR);
	~MinWin();
private:
	QLineEdit *senderPortLineEdit, *senderAddressLineEdit;
	QTextEdit *senderContentTextEdit;
	
	UdpListener *listener;
};
