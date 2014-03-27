#include "qt.h"
#include <QtWidgets/QApplication>
#include <Box2D.h>
#include <fstream>
#include "DLL_SAMPLE.h"

using namespace std;

#pragma comment(lib,"Box2D.lib")
#pragma comment(lib,"DLLTEST.lib")

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	qt w;
	w.show();
	return a.exec();
}
