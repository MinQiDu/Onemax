#include "ExhaustiveSearch.h"
#include <cmath>  /* 為了使用power次方公式 */
#include <chrono> /* 為了使用時間計算 */

using namespace std;
using namespace chrono;

void algo_ES::RunALG(int _bit)
{
    bit = _bit;

    uint64_t total_possibility = (bit == 64) ? UINT64_MAX : (1ULL << bit); /* 2^bit = bit數的總可能性 */

    auto start = steady_clock::now(); /*for 時間計算*/

    Reset();
    int best_value = -1;
    int value;
    vector<int> best_sol;
    vector<int> sol(bit, 0);

    while (count < total_possibility) /* ES就是窮舉到全部可能性都跑過 */
    {
        if (duration_cast<minutes>(steady_clock::now() - start).count() >= 30)
        {
            break;
        };

        for (int b = 0; b < bit; ++b) /* 對此nfes值轉換成binary vector */
        {
            sol[b] = (count >> b) & 1;
        };

        Evaluation(sol, value);

        if (value > best_value) /* 如果evaluate後的sol有比當前最優還好，就更新 */
        {
            best_sol = sol;
            best_value = value;
            cout << "[Evaluation count = " << count << "] Found better: " << value << " → ";
            for (int i = bit - 1; i >= 0; --i)
                cout << sol[i];
            cout << endl;
        };
    };
    cout << "Best Value : " << best_value << " Best Solution : ";
    for (int b = bit - 1; b >= 0; --b) /* 從最高位bit由右至左輸出 */
        cout << best_sol[b];
    cout << endl;
};

void algo_ES::Evaluation(const vector<int> &sol, int &value)
{
    value = OneMaxProblem(sol, bit); /* 繼承OneMax.cpp */
    count++;
};
void algo_ES::Reset()
{
    count = 0;
};