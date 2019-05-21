#include "QtGuiApplication1.h"
#include <qtextcodec.h>

MinWin::MinWin(QWidget *parent)
	: QMainWindow(parent)
	, listener(new UdpListener(rand(),parent))
{
	QTextCodec *codec = QTextCodec::codecForName("GBK");
	senderPortLineEdit = new QLineEdit;
	senderPortLineEdit->setReadOnly(true);
	senderAddressLineEdit = new QLineEdit;
	senderAddressLineEdit->setReadOnly(true);
	senderContentTextEdit = new QTextEdit;
	senderContentTextEdit->setReadOnly(true);

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(new QLabel(codec->toUnicode("发送方地址 ")), 0, 0);
	layout->addWidget(new QLabel(codec->toUnicode("发送方地址 ")), 1, 0);
	layout->addWidget(senderAddressLineEdit, 0, 1);
	layout->addWidget(senderPortLineEdit, 1, 1);
	layout->addWidget(senderContentTextEdit, 2, 0, 1, 2);

	QWidget *cw = new QWidget;
	cw->setLayout(layout);
	setCentralWidget(cw);

	connect(listener,static_cast<void(UdpListener::*)(QNetworkDatagram)>(&UdpListener::receiveDatagrams)
		, [&](QNetworkDatagram d) {
		senderAddressLineEdit->setText(d.senderAddress().toString());
		senderPortLineEdit->setText(QString::number(d.senderPort()));
		senderContentTextEdit->setText(d.data());
	});

}

MinWin::~MinWin()
{
}
