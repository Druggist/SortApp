#ifndef GENERATESEQUENCE
#define GENERATESEQUENCE

#include <iostream>
#include <ctime>
#include <cstdlib>

class GenerateSequence
{
public:
    int *Value;
    GenerateSequence();
    ~GenerateSequence();
    int GenerateIncreasing(int);
    int GenerateDecreasing(int);
    int GenerateConstant(int);
    int GenerateRandom(int);
    int GenerateAShaped(int);
private:
    int RandomNumber();
    int DeleteArray();
};
#endif // GENERATESEQUENCE

