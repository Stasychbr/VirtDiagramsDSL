#include "dpidialog.h"
#include "ui_dpidialog.h"

DpiDialog::DpiDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DpiDialog)
{
    ui->setupUi(this);
    connect(this, &DpiDialog::accepted, this, &DpiDialog::rememberDpi);
    connect(this, &DpiDialog::rejected, this, &DpiDialog::restoreDpi);

    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setMaximum((int)(sizeof(dpiValues) / sizeof(typeof(*dpiValues))) - 1);
    ui->horizontalSlider->setValue(startIdx);
    ui->horizontalSlider->setTracking(true);
    ui->dpi_label->setText(QString::number(dpiValues[startIdx]));
}

int DpiDialog::getDpi()
{
    return dpiValues[m_curDpiIdx];
}

void DpiDialog::on_horizontalSlider_valueChanged(int value)
{
    m_curDpiIdx = value;
    ui->dpi_label->setText(QString::number(getDpi()));
}

void DpiDialog::rememberDpi()
{
    m_prevDpiIdx = m_curDpiIdx;
}

void DpiDialog::restoreDpi()
{
    m_curDpiIdx = m_prevDpiIdx;
    ui->dpi_label->setText(QString::number(getDpi()));
    ui->horizontalSlider->setValue(m_curDpiIdx);
}

DpiDialog::~DpiDialog()
{
    delete ui;
}
