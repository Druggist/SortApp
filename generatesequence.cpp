#include "generatesequence.h"

GenerateSequence::GenerateSequence()
{

}

GenerateSequence::GenerateConstant(int Size)
{
    if(Value != NULL) DeleteArray();
    int x = RandomNumber();
    Value = new int[Size];
    for(int i=0;i<Size;i++) Value[i]=x;
    return 0;
}

GenerateSequence::GenerateIncreasing(int Size)
{
    if(Value != NULL) DeleteArray();
    Value = new int[Size];
    for(int i=0;i<Size;i++) Value[i]=i;
    return 0;
}

GenerateSequence::GenerateDecreasing(int Size)
{
    if(Value != NULL) DeleteArray();
    Value = new int[Size];
    for(int i=0;i<Size;i++) Value[i]=Size-i;
    return 0;
}

GenerateSequence::GenerateRandom(int Size)
{
    if(Value != NULL) DeleteArray();
    Value = new int[Size];
    for(int i=0;i<Size;i++) Value[i]=RandomNumber();
    return 0;
}

GenerateSequence::GenerateAShaped(int Size)
{
    if(Value != NULL) DeleteArray();
    Value = new int[Size];
    for(int i=0;i<Size;i++)
    {
        if(i<=Size/2) Value[i]=i;
        else Value[i]=Value[Size/2]+(Size/2-i);
    }
    return 0;
}

GenerateSequence::RandomNumber()
{
return  rand()%1000;
}

GenerateSequence::DeleteArray()
{
    delete [] Value;
    return 0;
}

GenerateSequence::~GenerateSequence()
{
    DeleteArray();
    Value=NULL;
}
