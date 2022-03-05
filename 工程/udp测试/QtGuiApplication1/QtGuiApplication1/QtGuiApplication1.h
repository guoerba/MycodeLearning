#pragma once

#include <QtWidgets/QMainWindow>
#include <qlineedit.h>
#include <qtextedit.h>
#include <qlabel.h>
#include <qgridlayout.h>
#include <qgroupbox.h>
#include <qpushbutton.h>
#include <qstatusbar.h>
#include <qthread.h>
#include <qdatetime.h>
#include <qlistwidget.h>
#include <qsplitter.h>
#include "UdpListener.h"
#include "UdpSender.h"
#include "ThreadPool.h"

class MinWin : public QMainWindow
{
	Q_OBJECT;

public:
	MinWin(QWidget *parent = Q_NULLPTR);
	~MinWin();
signals:
	void SendDatagrams(const QString &srcaddr, const uint srcport, const QString &dstaddr, const uint dstport, const QString &data);
private:
	QLineEdit *dstPortLineEdit, *dstAddressLineEdit,*dstDataLineEdit;
	QTextEdit *contentTextEdit;
	QPushButton *sendBtn;

	UdpListener *listener;
	QString textsize;
	
	QGroupBox *dstInfoGroupBox(QTextCodec *codec);
	QGroupBox *dstdataGroupBox(QTextCodec *codec);
	QGroupBox *windowGroupBox(QTextCodec *codec);

	QListWidget *portListWidget;

	QString RichText(const QString &size, const char *color, const QString &str);
	void CreateThreadPool(int size);
	void ShowMsg(const QString &dt, const QString &addr, const QString &port, const QString &d);

	uint curport;
};
