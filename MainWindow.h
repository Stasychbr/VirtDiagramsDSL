#pragma once

#include <QMainWindow>
#include <QFileDialog>
#include <QScrollBar>
#include "dpidialog.h"
#include "ErrorListener.h"

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
    void onShowLogger(bool checked);
    void onError(size_t line, size_t charPos, const std::string& msg);

private:
    void initDialogs();
    void proceedGrammar(QFileInfo path);
    void drawImage(QPaintDevice* paintDevice);
    void log(QString msg);

    int scaleState = 0;
    float saveScale;
    QFileInfo curFileName;
    QString winName;

	Ui::MainWindow *ui;

    DpiDialog* dpiDialog = nullptr;
    QFileDialog* openDialog = nullptr;
    QFileDialog* saveDialog = nullptr;
    QScrollBar* vertScroll = nullptr;
    ErrorListener* errorListener = nullptr;
};

