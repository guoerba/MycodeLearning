#include "Sender.h"
#include <stdlib.h>
#include <chrono>
#include <ctime>


Sender::Sender()
{
}


Sender::~Sender()
{
	delete s;
}

Sender::Sender(QHostAddress address, uint port, QObject *parent)
	: QObject(parent)
{
	srand(std::chrono::seconds(std::time(NULL)).count());
	s = new QUdpSocket;
	s->bind();
	s->writeDatagram((QString::number(rand())).toLatin1(), address, port);
}

