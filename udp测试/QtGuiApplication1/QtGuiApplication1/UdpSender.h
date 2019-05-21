#pragma once
#include <qobject.h>
#include <QtNetwork/qudpsocket.h>

class UdpSender : public QObject
{
	Q_OBJECT;
public:
	UdpSender(QHostAddress address,uint port, QObject *parent = NULL);
	~UdpSender();
private:
	QUdpSocket *s;
};

