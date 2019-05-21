#include "UdpSender.h"
#include <stdlib.h>
#include <chrono>
#include <ctime>

UdpSender::UdpSender(QHostAddress address, uint port, QObject *parent)
	: QObject(parent)
{
	srand(std::chrono::seconds(std::time(NULL)).count());
	s = new QUdpSocket;
	s->bind();
	s->writeDatagram((QString::number(rand())).toLatin1(), address, port);
}


UdpSender::~UdpSender()
{
	delete s;
}
