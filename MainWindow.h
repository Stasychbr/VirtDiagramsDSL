#pragma once

#include <QMainWindow>
#include <QFileDialog>
#include <QScrollBar>
#include "dpidialog.h"

#include "ErrorListener.h"
#include "HighlightableButton.h"

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
    void onError(size_t line, size_t charPos, const std::string& msg);

	void onLoggerButton(bool checked);

private:
    void initDialogs();
    void initStatusBar();
    void proceedGrammar(QFileInfo path);
    void drawImage(QPaintDevice* paintDevice);
    void log(QString msg);

	void highlightLoggerButton();

    int m_scaleState = 0;
    float m_saveScale;
    QFileInfo m_curFileName;

	Ui::MainWindow *ui;

    DpiDialog* m_dpiDialog = nullptr;
    QFileDialog* m_openDialog = nullptr;
    QFileDialog* m_saveDialog = nullptr;
    QScrollBar* m_vertScroll = nullptr;
    ErrorListener* m_errorListener = nullptr;

    QLabel* m_filenameLabel = nullptr;
    QLabel* m_dpiLabel = nullptr;

    bool m_fLoggerShown = false;
	HighlightableButton* m_loggerButton;
};

