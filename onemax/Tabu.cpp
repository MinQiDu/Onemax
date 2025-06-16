#include "OneMax.h"
#include "Tabu.h"
#include <deque>
#include <cstdlib>
#include <ctime>
using namespace std;

void algo_TB::RunALG(const int& _bit,
	                 const int& _run,
	                 const int& _iter,
	                 const int& _tweak_num,
	                 const int& _tabu_size)
{
	srand(time(NULL));
	bit = _bit;
	run = _run;
	mnfes = _iter;
	int tweak_num = _tweak_num;
	int tabu_size = _tabu_size;
	deque<vector<int>> tabulist;
	vector<int> sol = Init();

	while (nfes < mnfes)
	{
		if (tabulist.size() > tabu_size) /*check if list overflow*/
		{
			tabulist.pop_front();
		}

		vector<int> t_sol = Tweak(sol);

		for (int i = 0; i < tweak_num; ++i)
		{
			vector<int> tt_sol = Tweak(t_sol);

			bool tt_sol_not_in_tabulist = find(tabulist.begin(), tabulist.end(), tt_sol) == tabulist.end();
			bool t_sol_in_tabulist = find(tabulist.begin(), tabulist.end(), t_sol) != tabulist.end();

			if (tt_sol_not_in_tabulist 
				&& (Evaluation(tt_sol) > Evaluation(t_sol) || t_sol_in_tabulist))
			{
				t_sol = tt_sol;
			}
		}

		bool t_sol_not_in_tabulist = find(tabulist.begin(), tabulist.end(), t_sol) == tabulist.end();
		
		if (t_sol_not_in_tabulist)
		{
			sol = t_sol;
			tabulist.push_back(t_sol);
		}

		if (Evaluation(sol) > best_fit)
		{
			best_sol = sol;
			best_fit = Evaluation(best_sol);
		}
	}

}

vector<int> algo_TB::Init()
{
	nfes = 0;
	vector<int> sol(bit);
	for (int i = 0; i < bit; ++i)
	{
		sol[i] = rand() % 2;
	}
	best_sol = sol;
	best_fit = 0;
	return sol;
}

vector<int> algo_TB::Tweak(const vector<int>& origin_sol)
{

}

int algo_TB::Evaluation(const vector<int>& sol)
{
}