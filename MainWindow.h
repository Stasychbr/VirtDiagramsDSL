#pragma once

#include <QMainWindow>

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	MainWindow();

Q_SIGNALS:
	void testSignal();
};

