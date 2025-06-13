#include "ExhaustiveSearch.h"
#include <cmath>  /* ���F�ϥ�power���褽�� */
#include <chrono> /* ���F�ϥήɶ��p�� */

using namespace std;
using namespace chrono;

void algo_ES::RunALG(int _bit)
{
    bit = _bit;

    uint64_t total_possibility = (bit == 64) ? UINT64_MAX : (1ULL << bit); /* 2^bit = bit�ƪ��`�i��� */

    auto start = steady_clock::now(); /*for �ɶ��p��*/

    Reset();
    int best_value = -1;
    int value;
    vector<int> best_sol;
    vector<int> sol(bit, 0);

    while (count < total_possibility) /* ES�N�O�a�|������i��ʳ��]�L */
    {
        if (duration_cast<minutes>(steady_clock::now() - start).count() >= 30)
        {
            break;
        };

        for (int b = 0; b < bit; ++b) /* �惡nfes���ഫ��binary vector */
        {
            sol[b] = (count >> b) & 1;
        };

        Evaluation(sol, value);

        if (value > best_value) /* �p�Gevaluate�᪺sol�����e���u�٦n�A�N��s */
        {
            best_sol = sol;
            best_value = value;
            cout << "[Evaluation count = " << count << "] Found better: " << value << " �� ";
            for (int i = bit - 1; i >= 0; --i)
                cout << sol[i];
            cout << endl;
        };
    };
    cout << "Best Value : " << best_value << " Best Solution : ";
    for (int b = bit - 1; b >= 0; --b) /* �q�̰���bit�ѥk�ܥ���X */
        cout << best_sol[b];
    cout << endl;
};

void algo_ES::Evaluation(const vector<int> &sol, int &value)
{
    value = OneMaxProblem(sol, bit); /* �~��OneMax.cpp */
    count++;
};
void algo_ES::Reset()
{
    count = 0;
};