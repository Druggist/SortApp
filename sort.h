#ifndef SORT_H
#define SORT_H

#include <QObject>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <stdlib.h>

class Sort : public QObject
{
    Q_OBJECT
public:
    explicit Sort(QObject *parent = 0);
    time_t Time;
    double TimeInSec;
    int *Value;
    void SelectionSort(int*, int);
    void InsertionSort(int*, int);
    void ShellSort(int*, int);
    ~Sort();

private:
    void DeleteArray();

signals:
    void CurrentProgress_change(double);
};

#endif // SORT_H
