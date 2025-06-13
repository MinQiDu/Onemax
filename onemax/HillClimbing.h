#ifndef HILLCLIMBING_H
#define HILLCLIMBING_H

#include "OneMax.h"
#include <iostream>
#include <vector>

using namespace std;

class algo_HC : OneMax
{
public:
    void RunALG(int, int, int);

private:
    /* Input from Command - line Argument */
    int bit;
    int run;

    /* calculate the evaluation */
    int nfes; /* Number of Function Evaluations So far */
    int mnfes;

    vector<int> Init(); /* ���ͪ�l�� */

    vector<int> Neighbor(const vector<int> &); /* �F�~���;� */

    void Evaluation(const vector<int>&, int&);

    void Reset();
};

#endif