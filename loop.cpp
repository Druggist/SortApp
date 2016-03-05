#include "loop.h"

Loop::Loop(QObject *parent) : QObject(parent)
{
    Sequence = new GenerateSequence();
    SortedSequence = new Sort();
    TempFile = new QFile("temp.txt");
    if(TempFile->exists()) TempFile->remove();
}

void Loop::on_CurrentProgress_change(double Value)
{
    emit CurrentProgress_change(Value);
}

int Loop::Compute(int ElementsCount, int LoopTimes, int SortType, int SequenceType)
{
    QObject::connect(SortedSequence,&Sort::CurrentProgress_change,this,&Loop::on_CurrentProgress_change);
    emit OverallProgress_reset();
    if(TempFile->exists()) TempFile->remove();
    WriteLine("Elements Time");
    QThread::currentThread()->msleep(500);
    int Interval = ElementsCount/LoopTimes;
    double OverallProgress = 100.0/LoopTimes;
    Elements.resize(LoopTimes);
    Time.resize(LoopTimes);
    for(int i = Interval; i<ElementsCount; i+=Interval){
        GenerateAndSort(i, SortType, SequenceType);
        OverallProgress_change(OverallProgress);
        emit CurrentProgress_reset();
        WriteLine(QString::number(i)+" "+QString::number(SortedSequence->TimeInSec));
        Elements[i/Interval-1] = i;
        Time[i/Interval-1] = SortedSequence->TimeInSec;
    }
    emit CurrentProgress_reset();
    GenerateAndSort(ElementsCount, SortType, SequenceType);
    OverallProgress_change(OverallProgress);
    WriteLine(QString::number(ElementsCount)+" "+QString::number(SortedSequence->TimeInSec));
    Elements[LoopTimes-1] = ElementsCount;
    Time[LoopTimes-1] = SortedSequence->TimeInSec;
    QThread::currentThread()->msleep(1500);
    emit Vectors_compute(Elements, Time);
    emit OverallProgress_reset();
    emit CurrentProgress_reset();
    emit Finished();
    return 0;
}

void Loop::GenerateAndSort(int ElementsCount, int SortType, int SequenceType)
{
    switch (SequenceType) {
    case 0:
        Sequence->GenerateIncreasing(ElementsCount);
        break;
    case 1:
        Sequence->GenerateDecreasing(ElementsCount);
        break;
    case 2:
        Sequence->GenerateConstant(ElementsCount);
        break;
    case 3:
        Sequence->GenerateRandom(ElementsCount);
        break;
    case 4:
        Sequence->GenerateAShaped(ElementsCount);
        break;
    default:
        break;
    }

    switch (SortType) {
    case 0:
        SortedSequence->SelectionSort(Sequence->Value, ElementsCount);
        break;
    case 1:
        SortedSequence->InsertionSort(Sequence->Value, ElementsCount);
        break;
    case 2:
        SortedSequence->ShellSort(Sequence->Value, ElementsCount);
        break;
    default:
        break;
    }
}

void Loop::WriteLine(QString Line)
{
    if (!TempFile->open(QIODevice::Append)) return;
    QTextStream Stream(TempFile);
    Stream << Line << endl;
    TempFile->close();
}
