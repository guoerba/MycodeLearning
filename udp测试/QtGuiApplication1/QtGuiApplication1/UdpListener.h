#pragma once

#include <QtNetwork/qudpsocket.h>
#include <QtNetwork/qtcpsocket.h>
#include <QtNetwork/qnetworkdatagram.h>
#include <stdlib.h>
#include <chrono>
#include <ctime>

typedef unsigned int		uint;
typedef std::string			String;
class UdpListener : public QObject
{
	Q_OBJECT;
public:
	UdpListener(QObject *parent = NULL);
	UdpListener(uint port,QObject *parent = NULL);
	UdpListener(const QString &addr, uint port, QObject *parent = NULL);
	~UdpListener();
	void SendMsg(const char *msg,QHostAddress address,uint port);//套接字发送数据报
	void SendMsg(const QString &msg, QHostAddress address, uint port);
	void SendDatagrams(const QString &srcaddr, const uint srcport, const QString &dstaddr, const uint dstport, const QString &data);//输送数据到从机，从界面向套接字输送数据
	QString address() const;
	uint port() const;
	void SendLocalPort();
signals:
	void receiveDatagrams(QNetworkDatagram);
	void SendPort(const uint port);//告诉线程池实际绑定的端口
private:
	void readPendingDatagrams();
	uint m_port;
	QHostAddress m_addr;

	QUdpSocket *s;
	QVector<QNetworkDatagram>d;
};
