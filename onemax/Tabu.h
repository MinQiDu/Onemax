#ifndef TABU_H
#define TABU_H

#include "OneMax.h"

class algo_TB
{
public :
	void RunALG(const int &bit, 
		        const int &run,
		        const int &iter,
	            const int &tweak_num,
	            const int &tabu_size);                /*執行TabuSearch*/
private :
	int bit;
	int run; 
	int iter;                                         /*每run evaluation times*/

	int mnfes;                                        /*max evaluation times= iter*/
	int nfes;                                         /*當前evaluation times*/

	vector<int> best_sol;
	int best_fit;

	vector<int> Init();                               /*產生初始解並輸出，設定best_sol, best_fit初始值*/
	vector<int> Tweak(const vector<int> &origin_sol); /*微調origin_sol並輸出*/
	int Evaluation(const vector<int>& sol);           /*計算sol的onemax fitness，輸出fitness*/
};

#endif
