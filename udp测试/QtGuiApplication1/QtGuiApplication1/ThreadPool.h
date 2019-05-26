#pragma once
#include "UdpListener.h"
#include <qthread.h>
#include <qobject.h>
#include <map>
#include <queue>
#include <list>
#include <qhostaddress.h>
#include <qdatetime.h>
#include <qmutex.h>

struct Thread {
	uint ip;
	uint port;
	QThread *thread;
	Thread():thread(0),ip(0),port(0){}
	Thread(uint ip,uint port):thread(new QThread),ip(ip),port(port){}
	Thread(const QString &ip, uint port) :thread(new QThread), port(port) 
	{
		QHostAddress addr = QHostAddress(ip);
		this->ip = addr.toIPv4Address();
	}
	Thread(QThread *th ,const QString &ip, uint port) :thread(th), port(port)
	{
		QHostAddress addr = QHostAddress(ip);
		this->ip = addr.toIPv4Address();
	}
	Thread(QThread *th, uint &ip, uint port) :thread(th),ip(ip), port(port){}
	~Thread()
	{
		delete thread;
		thread = NULL;
	}
};

struct PortMsg {
	uint addr;
	uint port;

};

class ThreadPool : public QObject
{
	Q_OBJECT;
public:
	ThreadPool(QObject *parent = NULL);
	ThreadPool(uint size,QObject *parent = NULL);
	~ThreadPool();
	int AllocateTask(UdpListener *task);
signals:
	void SendMsg(const QString &dt,const QString &addr,const QString &port,const QString &d);//输送数据到屏幕显示
	void SendDatagrams(const QString &srcaddr, const uint srcport, const QString &dstaddr, const uint dstport, const QString &data);//输送数据到从机
	void SendAvailablePorts(QString ports);//向用户显示可用的端口
private:
	uint availableThreadCount;
	uint count;
	
	std::queue<Thread*>availableThread;
	std::list<Thread*>busyThread;
	std::list<uint>portlist;

	QMutex locker;
	//QString RichText(const QString &size, const char *color, const QString &str);
};

