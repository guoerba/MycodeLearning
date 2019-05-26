#include <qobject.h>
#include <QtNetwork/qudpsocket.h>
#pragma once
class Sender : public QObject
{
	Q_OBJECT
public:
	Sender();
	Sender(QHostAddress address, uint port, QObject *parent = NULL);
	~Sender();
private:
	QUdpSocket *s;
};

