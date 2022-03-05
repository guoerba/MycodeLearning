#include "UdpListener.h"
#include <iostream>
#include <qdebug.h>

UdpListener::UdpListener(QObject *parent)
	: QObject(parent)
	, d(QVector<QNetworkDatagram>())
	, m_port(0)
	, m_addr(QHostAddress())
{

}

UdpListener::UdpListener(uint port,QObject *parent)
	: QObject(parent)
	, d(QVector<QNetworkDatagram>())
	, m_port(port)
	, m_addr(QHostAddress(QHostAddress::LocalHost))
{
	s = new QUdpSocket;
	connect(s, &QUdpSocket::readyRead, this, &UdpListener::readPendingDatagrams);
	//connect(s, &QUdpSocket::bytesAvailable, this, &UdpListener::readPendingDatagrams);
	s->bind(QHostAddress::LocalHost, port, QAbstractSocket::ShareAddress| QAbstractSocket::ReuseAddressHint);
	//s->setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption, 1024 * 1024 * 100);
}

UdpListener::UdpListener(const QString &addr, uint port, QObject *parent)
	: QObject(parent)
	, d(QVector<QNetworkDatagram>())
	, m_port(port)
	, m_addr(QHostAddress(addr))
{

	s = new QUdpSocket;
	connect(s, &QUdpSocket::readyRead, this, &UdpListener::readPendingDatagrams);
	//connect(s, &QUdpSocket::bytesAvailable, this, &UdpListener::readPendingDatagrams);
	s->bind(QHostAddress(addr), port, QAbstractSocket::ShareAddress | QAbstractSocket::ReuseAddressHint);
	//s->setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption, 1024 * 1024 * 100);

}

UdpListener::~UdpListener()
{
	delete s;
	d.clear();
}

void UdpListener::SendMsg(const char * msg, QHostAddress address, uint port)
{
	long long int result = s->writeDatagram(msg, address, port);
	std::cout << "result: " << result << std::endl;
	if (result == -1)
		std::cout << "error code: " << (int)(s->error()) << std::endl;
}

void UdpListener::SendMsg(const QString & msg, QHostAddress address, uint port)
{
	long long int result = s->writeDatagram(msg.toLocal8Bit(), address, port);
	std::cout << "result: " << result << std::endl;
	if (result == -1)
		std::cout << "error code: " << (int)(s->error()) << std::endl;
}

void UdpListener::SendDatagrams(const QString &srcaddr, const uint srcport, const QString &dstaddr, const uint dstport, const QString &data)
{
	if (/*m_addr.isEqual(QHostAddress(srcaddr)) &&*/ (m_port == srcport))
	{
		std::cout << "in senddatagrams srcaddr: " << srcaddr.toStdString() << " srcport: " << srcport << " dstaddr: " << dstaddr.toStdString() << " dstport: " << dstport << std::endl;
		SendMsg(data, QHostAddress::LocalHost, dstport);
		/*if (dstaddr.isEmpty())
			SendMsg(data, QHostAddress::LocalHost, dstport);
		else
			SendMsg(data, QHostAddress(dstaddr), srcport);*/
	}
	
}

QString UdpListener::address() const
{
	return s->localAddress().toString();
}

uint UdpListener::port() const
{
	return s->localPort();
}

void UdpListener::SendLocalPort()
{
	m_port = s->localPort();
	emit SendPort(m_port);
}

void UdpListener::readPendingDatagrams()
{
	/*if (m_port == 0)
	{
		m_port = s->localPort();
		emit SendPort(m_port);
		return;
	}*/
	std::cout << "in readPendingDatagrams" << std::endl;
	while (s->hasPendingDatagrams())
	{
		QNetworkDatagram dg = s->receiveDatagram();
		emit receiveDatagrams(dg);
		std::cout << "receive data from: " << dg.destinationAddress().toString().toStdString()
			<< "/" << dg.destinationPort() << " data is : " << dg.data().toStdString() << std::endl;
	}
	/*while (s->hasPendingDatagrams())
	{
		QByteArray datagram;        
		datagram.resize(s->pendingDatagramSize());
		QHostAddress sender;        
		quint16 Pic_port;        
		s->readDatagram(datagram.data(), datagram.size(), &sender, &Pic_port);
		
		QNetworkDatagram dg(datagram,sender,Pic_port);
		emit receiveDatagrams(dg);
		std::cout << "receive data from: " << dg.destinationAddress().toString().toStdString()
			<< "/" << dg.destinationPort() << " data is : " << dg.data().toStdString() << std::endl;
	}*/
	//s->writeDatagram(QByteArray("received!"), d[0].senderAddress(), d[0].senderPort());
}
