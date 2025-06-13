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
    int iter;     /*世代數*/
    int pop_size; /*每個世代的人口數*/
    vector<vector<int>> population;
    vector<int> p1;
    vector<int> p2;
    vector<vector<int>> children;
    vector<int> fitness;

    /*calculate times of evaluation*/
    int nfes;
    int mnfes;

    void Init();              /*產生初始pop_size個解存入陣列population*/
    void Select_Roulette();   /*輪盤法select*/
    void Select_Tournament(); /*競賽法select*/
    void Mutation(vector<int> &child); /*adaptive mutation*/
    void Crossover_Unify(const vector<int> &p1, const vector<int> &p2, vector<int> &c1, vector<int> &c2);
    void Crossover_Mask(const vector<int> &p1, const vector<int> &p2, vector<int> &c1, vector<int> &c2);
    void Evaluation(const vector<int> &child, int &fitness);
    void Create_FitRecord(const string &filename, const vector<double> &content);
};