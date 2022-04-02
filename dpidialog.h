#ifndef DPIDIALOG_H
#define DPIDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QSlider>

namespace Ui {
class DpiDialog;
}

class DpiDialog : public QDialog
{
    Q_OBJECT

    static const inline int dpiValues[] = {50, 100, 150, 300, 400, 500, 600, 800, 1000, 1250, 1500};
    static const inline int startIdx = 6;
public:
    explicit DpiDialog(QWidget *parent = nullptr);
    int getDpi();
    ~DpiDialog();

private Q_SLOTS:

    void on_horizontalSlider_valueChanged(int value);

private:
    void rememberDpi();
    void restoreDpi();

    int curDpiIdx = startIdx;
    int prevDpiIdx = startIdx;

    QLabel* dpiLabel = nullptr;
    QSlider* slider = nullptr;

    Ui::DpiDialog *ui;
};

#endif // DPIDIALOG_H
