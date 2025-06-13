#ifndef EXHAUSTIVESEARCH_H
#define EXHAUSTIVESEARCH_H

#include "OneMax.h"
#include <iostream>
#include <vector>
#include <cstdint> /* ���F�ϥ� uint64_t bit = ����W�L64! */

using namespace std;

class algo_ES : OneMax
{
public:
    void RunALG(int);

private:
    /* input from command line argument */
    int bit;

    /* calculate times of evaluation */
    uint64_t count; /* �p��a�|���� */

    void Evaluation(const vector<int> &, int &);

    void Reset();
};

#endif