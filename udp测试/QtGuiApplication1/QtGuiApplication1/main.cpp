#include "QtGuiApplication1.h"
#include "UdpListener.h"
#include "UdpSender.h"
#include <QtWidgets/QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
	/*int flag;
	std::cin >> flag;
	if (flag)
	{
		UdpSender sender(QHostAddress::LocalHost, 50000);
	}
	else
	{
		UdpListener listener(50000);
	}*/
	srand(0);

	QApplication a(argc, argv);
	MinWin w;
	w.show();
	return a.exec();
}
