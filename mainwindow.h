#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <progressdialog.h>
#include <loop.h>
#include <qcustomplot.h>
#include <QFile>
#include <QThread>
#include <QtConcurrent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow(); 

private slots:
    void on_Run_clicked();

    void on_actionExit_triggered();

    void on_actionExport_triggered();

    void on_Loop_toggled(bool);

public slots:
    void on_CurrentProgress_change(double);
    void on_OverallProgress_change(double);
    void on_CurrentProgress_reset();
    void on_OverallProgress_reset();
    void on_Finish();

private:
    Ui::MainWindow *ui;
    Loop *Compute;
    ProgressDialog *Progress;
    QCustomPlot *Chart;
    QFuture<int> Task;
    void DrawChart(QVector<double>, QVector<double>);
};

#endif // MAINWINDOW_H
