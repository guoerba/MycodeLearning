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
	void SendMsg(const char *msg,QHostAddress address,uint port);//�׽��ַ������ݱ�
	void SendMsg(const QString &msg, QHostAddress address, uint port);
	void SendDatagrams(const QString &srcaddr, const uint srcport, const QString &dstaddr, const uint dstport, const QString &data);//�������ݵ��ӻ����ӽ������׽�����������
	QString address() const;
	uint port() const;
	void SendLocalPort();
signals:
	void receiveDatagrams(QNetworkDatagram);
	void SendPort(const uint port);//�����̳߳�ʵ�ʰ󶨵Ķ˿�
private:
	void readPendingDatagrams();
	uint m_port;
	QHostAddress m_addr;

	QUdpSocket *s;
	QVector<QNetworkDatagram>d;
};
