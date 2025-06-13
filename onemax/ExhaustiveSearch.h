#ifndef EXHAUSTIVESEARCH_H
#define EXHAUSTIVESEARCH_H

#include "OneMax.h"
#include <iostream>
#include <vector>
#include <cstdint> /* 為了使用 uint64_t bit = 不能超過64! */

using namespace std;

class algo_ES : OneMax
{
public:
    void RunALG(int);

private:
    /* input from command line argument */
    int bit;

    /* calculate times of evaluation */
    uint64_t count; /* 計算窮舉次數 */

    void Evaluation(const vector<int> &, int &);

    void Reset();
};

#endif