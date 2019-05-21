#include "QtGuiApplication1.h"
#include <qtextcodec.h>
#include <qdebug.h>
MinWin::MinWin(QWidget *parent)
	: QMainWindow(parent)
	, listener(new UdpListener(0,this))
{
	QTextCodec *codec = QTextCodec::codecForName("GBK");
	QGridLayout *layout = new QGridLayout;
	int n = 0;
	layout->addWidget(dstInfoGroupBox(codec), n++, 0);
	layout->addWidget(dstdataGroupBox(codec), n++, 0);
	layout->addWidget(windowGroupBox(codec), n++, 0);

	QWidget *cw = new QWidget;
	cw->setLayout(layout);
	setCentralWidget(cw);
	QString textsize = QString::number(contentTextEdit->font().pixelSize());
	//QString textsize = QString("5");
	this->statusBar()->showMessage(codec->toUnicode((tr("当前进程 %1/%2 ").arg(listener->address()).arg(listener->port())).toLatin1()));
	
	connect(sendBtn, &QPushButton::clicked, [&]() {
		QString addr = dstAddressLineEdit->text();
		uint port = dstPortLineEdit->text().toUInt(NULL);
		if (addr.isEmpty())
			listener->SendMsg(dstDataLineEdit->text(), QHostAddress::LocalHost, port);
		else
			listener->SendMsg(dstDataLineEdit->text(), QHostAddress(addr), port);
	});
	connect(listener, static_cast<void(UdpListener::*)(QNetworkDatagram)>(&UdpListener::receiveDatagrams)
		, [&,textsize](QNetworkDatagram d) {
		
		QString dt = RichText(textsize, "blue", QDateTime::currentDateTime().toString(QString("dd.MM.yyyy hh:mm:ss")));
		QString addr = QString("%1\\%2").arg(RichText(textsize, "green", d.senderAddress().toString()))
			.arg(RichText(textsize, "red", QString::number(d.senderPort())));
		contentTextEdit->textCursor().insertHtml(QString("(%1)From[%2] : %3").arg(dt).arg(addr).arg(QString(d.data())));
		contentTextEdit->append("\n");
	});
}

MinWin::~MinWin()
{
}

QGroupBox * MinWin::dstInfoGroupBox(QTextCodec *codec)
{
	dstAddressLineEdit = new QLineEdit;
	dstPortLineEdit = new QLineEdit;

	QGroupBox *g = new QGroupBox(codec->toUnicode("目的机器信息"),this);
	QGridLayout *layout = new QGridLayout;
	int n = 0;
	layout->addWidget(new QLabel(codec->toUnicode("IP ")),0,n++);
	layout->addWidget(dstAddressLineEdit, 0, n++);
	layout->addWidget(new QLabel(codec->toUnicode("端口 ")), 0, n++);
	layout->addWidget(dstPortLineEdit, 0, n++);
	g->setLayout(layout);
	return g;
}

QGroupBox * MinWin::dstdataGroupBox(QTextCodec *codec)
{
	dstDataLineEdit = new QLineEdit;
	sendBtn = new QPushButton(codec->toUnicode("发送"));

	QGroupBox *g = new QGroupBox(codec->toUnicode("输入数据"), this);
	QGridLayout *layout = new QGridLayout;
	int n = 0;
	layout->addWidget(dstDataLineEdit, 0, n++);
	layout->addWidget(sendBtn, 0, n++);
	g->setLayout(layout);
	return g;
}

QGroupBox * MinWin::windowGroupBox(QTextCodec *codec)
{
	contentTextEdit = new QTextEdit;
	contentTextEdit->setReadOnly(true);
	QGroupBox *g = new QGroupBox(codec->toUnicode("消息窗口"), this);
	QGridLayout *layout = new QGridLayout;
	layout->addWidget(contentTextEdit, 0, 0);
	g->setLayout(layout);
	return g;
}

QString MinWin::RichText(const QString &size, const char * color, const QString & str)
{
	return QString("<font size=\"%1\" color=\"%2\">%3</font>").arg(size).arg(color).arg(str);
}
