#include "progressdialog.h"
#include "ui_progressdialog.h"

ProgressDialog::ProgressDialog(QWidget *parent, Qt::WindowFlags f) :
    QDialog(parent, f),
    ui(new Ui::ProgressDialog)
{
    CurrentProgress = 0;
    OverallProgress = 0;
    ui->setupUi(this);
}

void ProgressDialog::UpdateCurrentProgress(double Progress)
{
    CurrentProgress += Progress;
    ui->CurrentProgress->setValue(CurrentProgress);
}

void ProgressDialog::UpdateOverallProgress(double Progress)
{
    OverallProgress += Progress;
    ui->OverallProgress->setValue(OverallProgress);
}

ProgressDialog::~ProgressDialog()
{
    delete ui;
}
