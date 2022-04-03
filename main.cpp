#include <QApplication>

#include "MainWindow.h"

int main(int argc, char* argv[]) {
    freopen( "freopen.out", "w", stderr);
	QApplication app(argc, argv);
	app.setWindowIcon(QIcon(":/icons/RailDSLIcon.ico"));
//    app.setStyle("Windows");
	MainWindow w;
    w.show();

	return app.exec();
}
