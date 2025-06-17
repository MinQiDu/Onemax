#include "OneMax.h"
#include "Tabu.h"
#include <deque>
#include <cstdlib>
#include <ctime>
#include <string>
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
	avg_record.resize(mnfes, 0);

	for (int i = 0; i < run; ++i)
	{   /*Initialization*/
		tabulist.clear();
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
		}
		Create_Record("fitness_of_run_" + to_string(i) + "_TB_" + to_string(bit) + "bit.txt", best_record);

		for (int j = 0; j < mnfes; ++j)
		{
			avg_record[j] += best_record[j];
		}
	}

	for (int k = 0; k < mnfes; ++k)
	{
		avg_record[k] /= run;
	}
	
	Create_Record("fitness_average_TB_" + to_string(bit) + "bit.txt", avg_record);

	ofstream plot("plot_TB.plt");
	plot << "set terminal png size 800, 600\n";
	plot << "set output 'result_onemax_TB_" << bit << "bit.png'\n";
	plot << "set title 'Average Convergence with TabuSearch on OneMax'\n";
	plot << "set xlabel 'Evaluation times'\n";
	plot << "set ylabel 'Average Fitness'\n";
	plot << "set xrange [0:" << mnfes << "]\n";
	plot << "set yrange [0:" << bit << "]\n";
	plot << "plot 'fitness_average_TB_" << bit << "bit.txt' using 1:2 with lines title 'Average with TB'\n";
	plot.close();
}

vector<int> algo_TB::Init()
{
	nfes = 0;
	vector<int> init_sol(bit);

	for (int i = 0; i < bit; ++i)
	{
		init_sol[i] = rand() % 2;
	}

	best_sol = init_sol;
	OneMax om;
	best_fit = om.OneMaxProblem(init_sol, bit);
	best_record.resize(mnfes);

	return init_sol;
}

vector<int> algo_TB::Tweak(const vector<int>& origin_sol)
{
	vector<int> new_sol = origin_sol;
	int rd_bit = rand() % bit;
	new_sol[rd_bit] = 1 - new_sol[rd_bit];
	return new_sol;
}

int algo_TB::Evaluation(const vector<int>& sol)
{
	int fit;
	OneMax om;
	fit = om.OneMaxProblem(sol, bit);

	if (fit > best_fit)
	{
		best_sol = sol;
		best_fit = fit;
	}

	best_record[nfes] = best_fit;
	nfes++;
	return fit;
}

void algo_TB::Create_Record(const string& filename, const vector<int>& content)
{
	ofstream file(filename);
	for (int i = 0; i < mnfes; ++i)
	{
		file << i+1 << " " << content[i] << "\n";
	}
	file.close();
}