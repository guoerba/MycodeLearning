#include "UdpSender.h"
#include <qtextcodec.h>
#include <QtNetwork/qnetworkdatagram.h>
UdpSender::UdpSender(QWidget *parent)
	: QMainWindow(parent)
{
	srand(std::chrono::seconds(std::time(NULL)).count());
	QTextCodec *codec = QTextCodec::codecForName("GBK");
	portLineEdit = new QLineEdit;
	dataLineEdit = new QLineEdit;
	sendBtn = new QPushButton(codec->toUnicode("发送"));

	QGridLayout *layout = new QGridLayout;
	int n = 0;
	layout->addWidget(new QLabel(codec->toUnicode("目的端口")), 0, 0);
	layout->addWidget(portLineEdit, 0, 1);
	layout->addWidget(dataLineEdit, 1, 0);
	layout->addWidget(sendBtn, 1, 1);

	QWidget *cw = new QWidget;
	cw->setLayout(layout);
	setCentralWidget(cw);

	s = new QUdpSocket;
	s->bind();

	connect(sendBtn, &QPushButton::clicked, [&]() {
		QByteArray b = dataLineEdit->text().toLatin1();
		QNetworkDatagram d(b,QHostAddress(QHostAddress::LocalHost), portLineEdit->text().toInt());
		s->writeDatagram(d);
	});
}
