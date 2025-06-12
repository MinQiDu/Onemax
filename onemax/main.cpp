#include "ExhaustiveSearch.h"
#include "HillClimbing.h"
#include "SimulatedAnnealing.h"
#include "GeneticAlgo.h"
#include <string> // 處理string

int main(int argc, char *argv[])
{
    int bit = atoi(argv[1]);
    int run = atoi(argv[2]);
    int iter = atoi(argv[3]);
    int pop_size = atof(argv[4]);
    string algo_type = argv[5]; // 選演算法

    if (algo_type == "ES") /*ExhaustiveSearch*/
    {
        algo_ES algo;
        algo.RunALG(bit);
    } /*還有條件需要判斷，不能加; !!!!!!*/

    else if (algo_type == "HC") /*HillClimbing*/
    {
        algo_HC algo;
        algo.RunALG(bit, run, iter);
    }
    else if (algo_type == "SA") /*SimulatedAnnealing*/
    {
        algo_SA algo;
        algo.RunALG(bit, run, iter);
    }
    else if (algo_type == "GA") /*GeneticAlgo*/
    {
        algo_GA algo;
        algo.RunALG(bit, run, iter, pop_size);
    }
    else
    {
        cout << "Choose Algorithm ( ES / HC / SA / GA )" << endl;
    }
}