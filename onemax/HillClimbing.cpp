#include "HillClimbing.h"
#include <cstdlib> /* for srand() */
#include <ctime>   /* for time() */
#include <fstream> /* �إ��ɮץ� */
#include <string>
using namespace std;

void algo_HC::RunALG(int _bit, int _run, int _iter)
{
    bit = _bit;
    run = _run;
    mnfes = _iter; /* ��evaluation���ƨ��Niteration�N�� */
    vector<int> record_sum(mnfes, 0);

    cout << "Bit : " << bit << " Run : " << run << " Mnfes : " << mnfes << " Algorithm : HillClimbing" << endl;

    srand(time(NULL));

    for (int r = 0; r < run; ++r)
    {
        Reset();
        vector<int> best_sol = Init();
        int best_value = OneMaxProblem(best_sol, bit); /* ����X�o�@run��l��sol�Mvalue�A�]��best */
        cout << "\n----------------" << " Run : " << r + 1 << " ----------------" << endl;
        vector<int> record(mnfes); /* for recording value of every iteration */

        while (nfes < mnfes) /* ��evaluation�����٨S�F��]�w�ȡA�~����� */
        {
            /* ���;F�~ */
            vector<int> sol = Neighbor(best_sol);
            /* �����F�~ */
            int value;
            Evaluation(sol, value);
            /* ��s���u�� */
            if (value > best_value)
            {
                best_value = value;
                best_sol = sol;
                cout << "Evaluation count : " << nfes << " New Best : " << best_value << endl;
            };

            record[nfes - 1] = best_value;      /* ������run���C��iter�ƭ� */
            record_sum[nfes - 1] += best_value; /* �[�i�C��iter�`�M����K�᭱�⥭�� */

            /*if (nfes % 200 == 0)
            {
                cout << "Evaluation count : " << nfes << " New Best : " << best_value << endl;
            };*/
        }
        cout << "[ Best value ] : " << best_value << endl;

        ofstream file("values_of_run_" + to_string(r + 1) + "_HC.txt"); /* �بC�@run��iter���G�ɮ� */
        for (int n = 0; n < mnfes; ++n)
        {
            file << n + 1 << " " << record[n] << "\n";
        }
        file.close();

        /*cout << "\n\nRun" << r + 1 << " : ";
        for (int b = 0; b < bit; ++b)
        {
            cout << record[b] << " ";
        }*/
    }

    ofstream average("values_average_HC.txt"); /* �إߥ������� */
    for (int i = 0; i < mnfes; ++i)
    {
        average << i + 1 << " " << (double)record_sum[i] / run << "\n";
    }
    average.close();
    /*cout << "\n\nAverage : " << endl;
    for (int i = 0; i < mnfes; ++i)
    {
        cout << i << " " << record_sum[i] / run << "\n";
    }*/

    ofstream plt("plot_HC.plt");
    plt << "set terminal png size 800, 600\n";
    plt << "set output 'result_OneMax_HillClimbing.png'\n";
    plt << "set title 'Average Convergence with HillClimbing on OneMax'\n";
    plt << "set xlabel 'Iteration'\n";
    plt << "set ylabel 'Average Value'\n";
    plt << "set xrange [0:" << mnfes << "]\n";
    plt << "set yrange [0:" << bit << "]\n"; /* �ھڧA��J�� bit �]�w */
    plt << "plot 'values_average_HC.txt' using 1:2 with lines title 'Average with HillClimbing'\n";
    plt.close();
};

vector<int> algo_HC::Init()
{
    /*���ͤ@���H����lsol*/
    vector<int> random_sol(bit);
    for (int i = 0; i < bit; ++i)
    {
        random_sol[i] = rand() % 2;
    };
    return random_sol;

    /*���ͥ�0��sol*/
    /*vector<int> zero_sol(bit, 0);
    return zero_sol;*/
};

vector<int> algo_HC::Neighbor(const vector<int> &sol)
{
    int idx = rand() % bit; /* flip one random bit */
    vector<int> neighbor = sol;
    neighbor[idx] = 1 - neighbor[idx];
    return neighbor;
};

void algo_HC::Evaluation(const vector<int>& sol, int& value)
{
    value = OneMaxProblem(sol, bit);
    nfes++;
};

void algo_HC::Reset()
{
    nfes = 0;
};