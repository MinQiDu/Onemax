#ifndef SIMULATEDANNEALING_H
#define SIMULATEDANNEALING_H

#include "OneMax.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class algo_SA : OneMax
{
public:
    void RunALG(int bit, int run, int iter);

private:
    int bit;
    int run;
    int iter;    /*max counts of iteration*/
    int i_count; /*counts of iteration*/
    double temp;
    double cool_rate;
    double reheat_rate;
    double min_temp;

    void Init(vector<int> &sol, int &value);                                    /*隨機產生初始解*/
    vector<int> Neighbor(const vector<int> &sol);                               /*多點變異產生鄰居*/
    void Evaluation(const vector<int> &sol, int &value);                        /*計算新解的value*/
    void T_cooldown(double &temp);                                              /*降低溫度*/
    void T_reheat(double &temp);                                                /*升高溫度*/
    void Create_Vrecord(const string& filename, const vector<double>& content); /*create.txt to record values*/
};

#endif