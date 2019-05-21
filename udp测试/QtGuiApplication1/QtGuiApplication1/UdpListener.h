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
	~UdpListener();
	void SendMsg(const char *msg,QHostAddress address,uint port);
signals:
	void receiveDatagrams(QNetworkDatagram);
private:
	void readPendingDatagrams();

	QUdpSocket *s;
	QVector<QNetworkDatagram>d;
};
