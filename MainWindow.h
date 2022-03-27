#pragma once

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

    static constexpr float scaleFactor = 0.25;
    static constexpr int scaleTimes = 5;

public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private Q_SLOTS:
    void onOpenAction();
    void onSaveAction();
    void onSaveAsAction();
    void onSetDpi(QAction* action);
    void onZoomOut();
    void onZoomIn();

private:
    void proceedGrammar(QString path);
    void saveImage(QString path);

    int scaleState = 0;
    float saveScale;
	Ui::MainWindow *ui;
};

