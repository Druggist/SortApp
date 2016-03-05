#include "sort.h"

Sort::Sort(QObject *parent) : QObject(parent)
{

}

void Sort::SelectionSort(int *Sequence, int Size)
{
    if(Value != NULL) DeleteArray();
    Value = new int[Size];
    for(int i = 0;i < Size;i++) Value[i] = Sequence[i];

    Time = clock();
    int Min, Temp;
    double CurrentProgress = 100.0/Size;
    for (int i = 0; i < Size; i++)
    {
        Min = i;
        for (int j = i + 1; j < Size; j++)
            if (Value[j] < Value[Min]) Min = j;
        if(Min != i)
        {
            Temp = Value[Min];
            Value[Min] = Value[i];
            Value[i] = Temp;
        }
        emit CurrentProgress_change(CurrentProgress);
    }
    Time = clock() - Time;
    TimeInSec = (double)Time/CLOCKS_PER_SEC;
}

void Sort::InsertionSort(int *Sequence, int Size)
{
    if(Value != NULL) DeleteArray();
    Value = new int[Size];
    for(int i = 0;i < Size;i++) Value[i] = Sequence[i];

    Time = clock();
    int Current, Temp;
    double CurrentProgress = 100.0/Size;
    for (int i = 1; i < Size; i++)
    {
        Temp = Value[i];
        for (Current = i - 1; Current >= 0 && Value[Current] > Temp; Current--) Value[Current + 1] = Value[Current];
        Value[Current + 1] = Temp;
        emit CurrentProgress_change(CurrentProgress);
    }
    Time = clock() - Time;
    TimeInSec = (double)Time/CLOCKS_PER_SEC;
}

void Sort::ShellSort(int *Sequence, int Size)
{
    if(Value != NULL) DeleteArray();
    Value = new int[Size];
    for(int i = 0;i < Size;i++) Value[i] = Sequence[i];

    Time = clock();
    int Factor, Temp;
    double CurrentProgress;
    for (int Gap = Size / 2; Gap > 0; Gap /= 2)
    {
        CurrentProgress= 100/(Size/Gap);
        for (int i = Gap -1; i < Size; i++)
        {
            Temp = Value[i];
            for (Factor = i; Factor >= Gap && Temp < Value[Factor - Gap]; Factor -= Gap) Value[Factor] = Value[Factor - Gap];
            Value[Factor] = Temp;
        }
        emit CurrentProgress_change(CurrentProgress);
    }
    Time = clock() - Time;
    TimeInSec = (double)Time/CLOCKS_PER_SEC;
}

void Sort::DeleteArray()
{
    delete [] Value;
    Value = NULL;
}

Sort::~Sort()
{
    DeleteArray();

}
