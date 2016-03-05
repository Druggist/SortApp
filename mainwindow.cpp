#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Compute = new Loop();
    Progress = new ProgressDialog();
    Progress->setWindowModality(Qt::ApplicationModal);
    Progress->setWindowFlags(Qt::SubWindow);
    if(Compute->TempFile->exists()) Compute->TempFile->remove();
    Chart = ui->Chart;
    Chart->addGraph();
    Chart->graph(0)->setLineStyle(QCPGraph::lsLine);
    Chart->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
    Chart->xAxis->setLabel("Elements");
    Chart->yAxis->setLabel("Time");
    Chart->xAxis->setRange(0, 1000);
    Chart->yAxis->setRange(0, 0.1);
    Chart->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
    if(Compute != NULL && Compute->TempFile->exists()) Compute->TempFile->remove();
}

void MainWindow::on_Run_clicked()
{
    if(Compute == NULL) Compute = new Loop();
    connect(Compute,&Loop::CurrentProgress_change,this,&MainWindow::on_CurrentProgress_change);
    connect(Compute,&Loop::OverallProgress_change,this,&MainWindow::on_OverallProgress_change);
    connect(Compute,&Loop::CurrentProgress_reset,this,&MainWindow::on_CurrentProgress_reset);
    connect(Compute,&Loop::OverallProgress_reset,this,&MainWindow::on_OverallProgress_reset);
    connect(Compute,&Loop::Finished,this,&MainWindow::on_Finish);
    Progress->show();
    Task = QtConcurrent::run(this->Compute,&Loop::Compute,ui->ElementsCount->value(),ui->LoopTimes->value(),ui->SortType->currentIndex(),ui->SequenceType->currentIndex());
}

void MainWindow::DrawChart(QVector<double> Elements, QVector<double> Time)
{
    QPen Pen;
    Pen.setWidthF(3);
    switch (ui->SortType->currentIndex()) {
    case 0:
        Pen.setColor(QColor(255,100,100));
        break;
    case 1:
        Pen.setColor(QColor(100,255,100));
        break;
    case 2:
        Pen.setColor(QColor(100,100,255));
        break;
    default:
        break;
    }
    Chart->xAxis->setRange(0, Elements.last()+Elements.last()/20);
    Chart->yAxis->setRange(0, Time.last()+Time.last()/20);
    Chart->graph(0)->clearData();
    Chart->graph(0)->setPen(Pen);
    Chart->graph(0)->addData(Elements, Time);
    Chart->replot();
}

void MainWindow::on_Finish()
{
    if(Compute->TempFile->exists()) ui->actionExport->setEnabled(true);
    Progress->close();
    DrawChart(Compute->Elements, Compute->Time);
    delete Compute;
    Compute = NULL;
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionExport_triggered()
{
    QString Filename = QFileDialog::getSaveFileName(this, "Export data","exported.txt","Text file (*.txt)");
    QFile *TempFile = new QFile("temp.txt");
    if(QFile::exists(Filename)) QFile::remove(Filename);
    TempFile->copy(Filename);
}

void MainWindow::on_Loop_toggled(bool checked)
{
    ui->LoopTimes->setEnabled(checked);
    ui->LoopTimes->setValue(1);
}

void MainWindow::on_CurrentProgress_change(double Value)
{
    Progress->UpdateCurrentProgress(Value);
}

void MainWindow::on_OverallProgress_change(double Value)
{
    Progress->UpdateOverallProgress(Value);
}

void MainWindow::on_CurrentProgress_reset()
{
    Progress->CurrentProgress = 0;
    Progress->UpdateCurrentProgress(0);
}

void MainWindow::on_OverallProgress_reset()
{
    Progress->OverallProgress = 0;
    Progress->UpdateOverallProgress(0);
}
