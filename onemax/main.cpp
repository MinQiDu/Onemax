#include "ExhaustiveSearch.h"
#include "HillClimbing.h"
#include "SimulatedAnnealing.h"
#include "GeneticAlgo.h"
#include "Tabu.h"
#include <string> // 處理string
#include <algorithm> // for all_of(input.begin(), input.end(), ::isdigit) & transform(輸入起點, 輸入終點, 輸出起點, 處理函式);
#include <cctype> // for toupper() tolower()

bool is_num(const string& input)
{
    return !input.empty() && all_of(input.begin(), input.end(), ::isdigit);
}

int getline_and_check(const string& prompt)
{
    string input;

    while (true)
    {
        cout << prompt;
        getline(cin, input);
        if (is_num(input))
        {
            return stoi(input);
        }
        else
        {
            cout << "Please retype and make sure the form is number.\n";
        }
    }
}

int main(int argc, char *argv[])
{
    int bit = atoi(argv[1]);
    int run = atoi(argv[2]);
    int iter = atoi(argv[3]);
    int pop_size = atoi(argv[4]);
    string algo_type = argv[5];  /*選演算法*/
    transform(algo_type.begin(), /*防呆! 轉換algo_type成全大寫*/
        algo_type.end(), 
        algo_type.begin(), 
        toupper);

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
    else if (algo_type == "TB") /*TabuSearch*/
    {
        int tabu_size = getline_and_check("Please type tabu_size = ");
        int tweak_num = getline_and_check("Please type tweak_num = ");
        
        algo_TB algo;
        algo.RunALG(bit, run, iter, tabu_size, tweak_num);
    }
    else
    {
        cout << "Choose Algorithm ( ES / HC / SA / GA / TB )" << endl;
    }
}
