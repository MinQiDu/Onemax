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
	            const int &tabu_size);                /*����TabuSearch*/
private :
	int bit;
	int run; 
	int iter;                                         /*�Crun evaluation times*/

	int mnfes;                                        /*max evaluation times= iter*/
	int nfes;                                         /*��eevaluation times*/

	vector<int> best_sol;
	int best_fit;
	vector<int> best_record;                          /*�����C��evaluation time��best_fit�A�X�ϥ�*/
	vector<double> avg_record;                        /*�����Crun����fitness*/

	vector<int> Init();                               /*���ͪ�l�Ѩÿ�X�A�]�wbest_sol, best_fit��l��*/
	vector<int> Tweak(const vector<int> &origin_sol); /*�L��origin_sol�ÿ�X*/
	int Evaluation(const vector<int>& sol);           /*�p��sol��onemax fitness�A��Xfitness*/

	template<typename T>
	void Create_Record(const string& filename, const vector<T>& content)
	{
		ofstream file(filename);
		for (int i = 0; i < mnfes; ++i)
		{
			file << i + 1 << " " << content[i] << "\n";
		}
		file.close();
	}   /*���ͬ������e����r�ɡA�]����@�b�h�ث��O�W�ҥH�ϥ�template*/
};

#endif
