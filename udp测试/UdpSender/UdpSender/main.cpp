#include "UdpSender.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	UdpSender w;
	w.show();
	return a.exec();
}
