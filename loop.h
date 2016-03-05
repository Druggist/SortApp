#ifndef LOOP_H
#define LOOP_H

#include <QObject>
#include <QDialog>
#include <generatesequence.h>
#include <sort.h>
#include <QFile>
#include <QThread>
#include <QTextStream>

class Loop : public QObject
{
    Q_OBJECT
public:
    explicit Loop(QObject *parent = 0);
    int Compute(int ElementsCount, int LoopTimes, int SortType, int SequenceType);
    QVector<double> Elements, Time;
    QFile *TempFile;

signals:
    void Vectors_compute(QVector<double>, QVector<double>);
    void OverallProgress_change(double);
    void CurrentProgress_change(double);
    void CurrentProgress_reset();
    void OverallProgress_reset();
    void Finished();

public slots:
    void on_CurrentProgress_change(double);

private:
    GenerateSequence *Sequence;
    Sort *SortedSequence;
    void WriteLine(QString);
    void GenerateAndSort(int ElementsCount, int SortType, int SequenceType);
};

#endif // LOOP_H
