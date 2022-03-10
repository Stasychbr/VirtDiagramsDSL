#include <QApplication>

#include "MainWindow.h"

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	app.setWindowIcon(QIcon(":/icons/RailDSLIcon.ico"));

	MainWindow w;
	w.show();

	return app.exec();
}
