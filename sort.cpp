#include "sort.h"
#include <QDebug>

Sort::Sort(QObject *parent) : QObject(parent)
{

}

void Sort::SelectionSort(int *Sequence, int Size)
{
    FillArray(Sequence, Size);

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
    FillArray(Sequence, Size);

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
    FillArray(Sequence, Size);

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

void Sort::QuickSortRight(int *Sequence, int Size)
{
    FillArray(Sequence, Size);
    Time = clock();
    QuickSort(0, Size-1, false);
    Time = clock() - Time;
    TimeInSec = (double)Time/CLOCKS_PER_SEC;
}

void Sort::QuickSortRandom(int *Sequence, int Size)
{
    FillArray(Sequence, Size);
    Time = clock();
    QuickSort(0, Size-1, true);
    Time = clock() - Time;
    TimeInSec = (double)Time/CLOCKS_PER_SEC;
}

void Sort::QuickSort(int Left, int Right, bool isRandom)
{
    //TODO set current progress
 double CurrentProgress = 100.0/Right;
 int i = Left;
 int j = Right;
 int x = (isRandom)?(Value[Left+(rand()%(Right-Left))]):(Value[Right]);

 do {
     while(Value[i] < x) i++;
     while(Value[j] > x) j--;
     if (i <= j){
         int Temp = Value[i];
         Value[i] = Value[j];
         Value[j] = Temp;
         i++;
         j--;
     }
 } while(i <= j);
 emit CurrentProgress_change(CurrentProgress);
 if (Left < j) QuickSort(Left, j, isRandom);
 if (Right > i) QuickSort(i, Right, isRandom);
}

int Sort::Parent(int n)
{
   return n/2;
}

int Sort::LeftChild(int n)
{
    return (n != 0)?(2 * n + 1):(1);
}

int Sort::RightChild(int n)
{
    return (n != 0)?(2 * n + 2):(2);
}

void Sort::RebuildHeap(int Element, int UnsortedSize)
{
    int Child = LeftChild(Element);
    int Temp = 0;
    int BiggerElement = (Child <= UnsortedSize && Value[Child]>Value[Element])?(Child):(Element);
    Child = RightChild(Element);
    if (Child <= UnsortedSize && Value[Child]>Value[Element] && Value[BiggerElement] < Value[Child]) BiggerElement = Child;

    if(BiggerElement != Element){
        Temp = Value[BiggerElement];
        Value[BiggerElement] = Value[Element];
        Value[Element] = Temp;
        RebuildHeap(BiggerElement, UnsortedSize);
    }
}

void Sort::BuildHeap(int Size)
{
    for(int i = Size/2; i>=0; i--) RebuildHeap(i, Size);
}

void Sort::HeapSort(int *Sequence, int Size)
{
    FillArray(Sequence, Size);
    Time = clock();

    double CurrentProgress = 100.0/Size;
    BuildHeap(Size-1);
    for(int i = Size-1; i>=0; i--)
    {
        int Temp = Value[0];
        Value[0] = Value[i];
        Value[i] = Temp;
        RebuildHeap(0, i - 1);
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

void Sort::FillArray(int *Array, int Size)
{
    if(Value != NULL) DeleteArray();
    Value = new int[Size];
    for(int i = 0;i < Size;i++) Value[i] = Array[i];
}

Sort::~Sort()
{
    DeleteArray();

}
