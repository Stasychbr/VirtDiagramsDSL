#pragma once

#include <QMainWindow>
#include <QFileDialog>
#include "dpidialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

    static constexpr float scaleFactor = 1.25;
    static constexpr int scaleTimes = 5;

public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private Q_SLOTS:
    void onOpenAction();
    void onSaveAction();
    void onSaveAsAction();
    void onSetDpi();
    void onZoomOut();
    void onZoomIn();

private:
    void initDialogs();
    void proceedGrammar(QString path);
    void drawImage(QPaintDevice* paintDevice);

    int scaleState = 0;
    float saveScale;
	Ui::MainWindow *ui;

    DpiDialog* dpiDialog;
    QFileDialog* saveDialog;
};

