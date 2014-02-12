#include "qt.h"
#include <QtWidgets/QApplication>
#include <Box2D.h>
#include <fstream>

using namespace std;

#pragma comment(lib,"Box2D.lib")


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	qt w;
	w.show();
	return a.exec();
}
