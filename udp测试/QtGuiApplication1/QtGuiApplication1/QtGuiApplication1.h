#pragma once

#include <QtWidgets/QMainWindow>
#include <qlineedit.h>
#include <qtextedit.h>
#include <qlabel.h>
#include <qgridlayout.h>
#include <qgroupbox.h>
#include <qpushbutton.h>
#include <qstatusbar.h>4
#include <qthread.h>
#include <qdatetime.h>
#include "UdpListener.h"
#include "UdpSender.h"

class MinWin : public QMainWindow
{
	Q_OBJECT;

public:
	MinWin(QWidget *parent = Q_NULLPTR);
	~MinWin();
private:
	QLineEdit *dstPortLineEdit, *dstAddressLineEdit,*dstDataLineEdit;
	QTextEdit *contentTextEdit;
	QPushButton *sendBtn;

	UdpListener *listener;
	
	QGroupBox *dstInfoGroupBox(QTextCodec *codec);
	QGroupBox *dstdataGroupBox(QTextCodec *codec);
	QGroupBox *windowGroupBox(QTextCodec *codec);

	QString RichText(const QString &size, const char *color, const QString &str);
};
