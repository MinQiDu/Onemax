#include "OneMax.h"
#include <vector>
#include <string>
using namespace std;

class algo_GA : OneMax
{
public:
    void RunALG(int bit, int run, int iter, int pop_size);

private:
    /*input from command_line arguments*/
    int bit;
    int run;
    int iter;     /*�@�N��*/
    int pop_size; /*�C�ӥ@�N���H�f��*/
    vector<vector<int>> population;
    vector<int> p1;
    vector<int> p2;
    vector<vector<int>> children;
    vector<int> fitness;

    /*calculate times of evaluation*/
    int nfes;
    int mnfes;

    void Init();              /*���ͪ�lpop_size�ӸѦs�J�}�Cpopulation*/
    void Select_Roulette();   /*���L�kselect*/
    void Select_Tournament(); /*�v�ɪkselect*/
    void Mutation(vector<int> &child); /*adaptive mutation*/
    void Crossover_Unify(const vector<int> &p1, const vector<int> &p2, vector<int> &c1, vector<int> &c2);
    void Crossover_Mask(const vector<int> &p1, const vector<int> &p2, vector<int> &c1, vector<int> &c2);
    void Evaluation(const vector<int> &child, int &fitness);
    void Create_FitRecord(const string &filename, const vector<double> &content);
};