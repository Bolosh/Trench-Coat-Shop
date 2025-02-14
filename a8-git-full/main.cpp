#include <QtWidgets/QApplication>
#include "Starter.h"

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);

	Starter s;
	s.show();

	return a.exec();
}


