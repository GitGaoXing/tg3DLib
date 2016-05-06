#include "tgMainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	tgMainWindow w;
	w.show();
	return a.exec();
}
