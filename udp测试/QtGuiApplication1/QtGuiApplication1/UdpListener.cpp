#include "UdpListener.h"
#include <iostream>

UdpListener::UdpListener(QObject *parent)
	: QObject(parent)
	, d(QVector<QNetworkDatagram>())
{

}

UdpListener::UdpListener(uint port,QObject *parent)
	: QObject(parent)
	, d(QVector<QNetworkDatagram>())
{
	srand(std::chrono::seconds(std::time(NULL)).count());
	s = new QUdpSocket;
	s->bind(QHostAddress::LocalHost, port);
	this->connect(s, &QUdpSocket::readyRead, this, &UdpListener::readPendingDatagrams);
}

UdpListener::~UdpListener()
{
	delete s;
}

void UdpListener::SendMsg(const char * msg, QHostAddress address, uint port)
{
	s->writeDatagram((QString::number(rand())).toLatin1(), address, port);
}

void UdpListener::readPendingDatagrams()
{
	while (s->hasPendingDatagrams())	
		d.push_back(s->receiveDatagram());
	//将发送方ip,端口，数据显示在窗口中
	for (auto i : d)
	{
		/*std::cout << "sender's ip: " << i.senderAddress().toString().toStdString() << " port: "
			<< i.senderPort() << "\ndata: " << i.data().toStdString() << std::endl;*/
		emit receiveDatagrams(i);
	}
	
	s->writeDatagram(QByteArray("received!"), d[0].senderAddress(), d[0].senderPort());
}
