#include "OneMax.h"

int OneMax::OneMaxProblem(const vector<int> &sol, int bit_size)
{
    int sum = 0;
    for (int i = 0; i < bit_size; i++)
    {
        sum += sol[i];
    }
    return sum;
};