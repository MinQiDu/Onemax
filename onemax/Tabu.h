#ifndef TABU_H
#define TABU_H

#include "OneMax.h"
#include <fstream> /*for string in parameter*/
using namespace std;

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
	vector<int> best_record;                          /*紀錄每次evaluation time的best_fit，出圖用*/
	vector<double> avg_record;                        /*紀錄每run平均fitness*/

	vector<int> Init();                               /*產生初始解並輸出，設定best_sol, best_fit初始值*/
	vector<int> Tweak(const vector<int> &origin_sol); /*微調origin_sol並輸出*/
	int Evaluation(const vector<int>& sol);           /*計算sol的onemax fitness，輸出fitness*/

	template<typename T>
	void Create_Record(const string& filename, const vector<T>& content)
	{
		ofstream file(filename);
		for (int i = 0; i < mnfes; ++i)
		{
			file << i + 1 << " " << content[i] << "\n";
		}
		file.close();
	}   /*產生紀錄內容的文字檔，因為實作在多種型別上所以使用template*/
};

#endif
