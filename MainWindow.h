#pragma once

#include <QMainWindow>
#include <QFileDialog>
#include <QScrollBar>
#include "dpidialog.h"
#include "logwindow.h"

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
    void wheelEvent(QWheelEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
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

    DpiDialog* dpiDialog = nullptr;
    QFileDialog* openDialog = nullptr;
    QFileDialog* saveDialog = nullptr;
    QScrollBar* vertScroll = nullptr;
};

