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

    void Init(vector<int> &sol, int &value);                                    /*�H�����ͪ�l��*/
    vector<int> Neighbor(const vector<int> &sol);                               /*�h�I�ܲ����;F�~*/
    void Evaluation(const vector<int> &sol, int &value);                        /*�p��s�Ѫ�value*/
    void T_cooldown(double &temp);                                              /*���C�ū�*/
    void T_reheat(double &temp);                                                /*�ɰ��ū�*/
    void Create_Vrecord(const string& filename, const vector<double>& content); /*create.txt to record values*/
};

#endif