#include "ThreadPool.h"
#include <iostream>


ThreadPool::ThreadPool(QObject *parent)
	: QObject(parent)
	, availableThreadCount(0)
{
}


ThreadPool::ThreadPool(uint size,QObject *parent)
	: QObject(parent)
	, availableThreadCount(size)
	, count(size)
{
	for (int i = 0; i < size; i++)//Ԥ�ȴ���size���߳�
		availableThread.push(new Thread(0, 0));
	for (int i = 0; i < size; i++)
	{
		UdpListener *s = new UdpListener(0, 0);
		AllocateTask(s);
	}
}

ThreadPool::~ThreadPool()
{
	for (auto it = busyThread.begin(); it != busyThread.end(); ++it)
	{
		(*it)->thread->quit();
		delete (*it)->thread;
	}
}

int ThreadPool::AllocateTask(UdpListener * task)
{
	if (availableThread.empty())
	{
		return -1;
	}
	Thread *th = availableThread.front();
	th->ip = QHostAddress(task->address()).toIPv4Address();
	th->port = task->port();
	busyThread.push_back(th);
	availableThread.pop();
	task->moveToThread(th->thread);
	connect(th->thread, &QThread::finished,task,&UdpListener::deleteLater);
	connect(th->thread, &QThread::started, task, &UdpListener::SendLocalPort);
	//���ݷ���Ķ˿ں�
	connect(task, static_cast<void(UdpListener::*)(const uint)>(&UdpListener::SendPort)
		, [&](const uint port) {
		//locker.lock();
		portlist.push_back(port);
		uint psize = portlist.size();
		if (psize == count)
		{
			QString ports = QString();
			portlist.sort();
			for (auto it = portlist.begin(); it != portlist.end(); ++it)
				ports.append(QString::number(*it) + ' ');
			emit SendAvailablePorts(ports);
		}
		//locker.unlock();
	});
	//�յ��ӻ���udp���ݱ�����ͨ���̳߳ش��������
	connect(task, static_cast<void(UdpListener::*)(QNetworkDatagram)>(&UdpListener::receiveDatagrams)
		, [&](QNetworkDatagram d){
		emit SendMsg(QDateTime::currentDateTime().toString(QString("dd.MM.yyyy hh:mm:ss"))
			, d.senderAddress().toString(), QString::number(d.senderPort()), QString(d.data()));
	});
	//�ӽ��洫���������ݣ������Ǵ��䵽��Ӧ�˿ڵļ����߳���
	connect(this, static_cast<void(ThreadPool::*)(const QString&, const uint, const QString&, const uint, const QString&)>(&ThreadPool::SendDatagrams)
		, task, static_cast<void(UdpListener::*)(const QString&, const uint, const QString&, const uint, const QString&)>(&UdpListener::SendDatagrams));
	th->thread->start();
	//std::cout << "in allocateTask()" << std::endl;
	return 0;
}
