#include "dpidialog.h"
#include "ui_dpidialog.h"

DpiDialog::DpiDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DpiDialog)
{
    ui->setupUi(this);

    connect(this, &DpiDialog::accepted, this, &DpiDialog::rememberDpi);
    connect(this, &DpiDialog::rejected, this, &DpiDialog::restoreDpi);

    dpiLabel = findChild<QLabel*>("dpi_label");
    slider = findChild<QSlider*>();

    if (slider) {
        slider->setMinimum(0);
        slider->setMaximum((int)(sizeof(dpiValues) / sizeof(typeof(*dpiValues))) - 1);
        slider->setValue(startIdx);
        slider->setTracking(true);
    }
    if (dpiLabel) {
        dpiLabel->setText(QString::number(dpiValues[startIdx]));
    }
}

int DpiDialog::getDpi()
{
    return dpiValues[curDpiIdx];
}

void DpiDialog::on_horizontalSlider_valueChanged(int value)
{
    curDpiIdx = value;
    if (dpiLabel) {
        dpiLabel->setText(QString::number(getDpi()));
    }
}

void DpiDialog::rememberDpi()
{
    prevDpiIdx = curDpiIdx;
}

void DpiDialog::restoreDpi()
{
    curDpiIdx = prevDpiIdx;
    if (dpiLabel) {
        dpiLabel->setText(QString::number(getDpi()));
    }
    if (slider) {
        slider->setValue(curDpiIdx);
    }
}

DpiDialog::~DpiDialog()
{
    delete ui;
}
