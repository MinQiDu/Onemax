#include "GeneticAlgo.h"
#include <iostream>
#include <cstdlib> /*for srand()*/
#include <ctime>
#include <algorithm> /*std::min_element(), std::max_element()*/
#include <fstream>

void algo_GA::RunALG(int _bit, int _run, int _iter, int _pop_size)
{
    srand(time(NULL));
    bit = _bit;
    run = _run;
    iter = _iter;
    pop_size = _pop_size;
    mnfes = iter * pop_size;
    vector<double> fitness_history_avg(mnfes); /*sum the fitness of every evaluations upon all runs*/

    for (int r = 0; r < run; ++r) /*each run*/
    {
        Init();                            /*���ͪ�lpop_size�ӸѦs�J�}�Cpopulation*/
        fitness.resize(pop_size);          /*(private vector)�ŧi�}�Cvalue�s��l�Ѫ���*/
        for (int p = 0; p < pop_size; ++p) /*�p���l�Ѫ��Ȧs�J�}�Cvalue*/
        {
            fitness[p] = OneMaxProblem(population[p], bit);
        }
        vector<double> fitness_history; /*����fitness of evaluations in this run*/

        int best_child_fit = 0;

        while (nfes < mnfes) /*��times of evaluation �|���F�W���A�|�����e & ����A�������P*/
        {
            children.clear();

            if (nfes < 0) /*�e�� : (diverse)���L�k select + uniform crossover*/
            {
                while (children.size() < pop_size) /*�]���@���|�ͨ��child�ҥH������children�Ӽƭp�����M��*/
                {
                    vector<int> c1(bit);             /*child1*/
                    vector<int> c2(bit);             /*child2*/
                    Select_Roulette();               /*�e���ν��L�k��X���parents p1 p2*/
                    Crossover_Unify(p1, p2, c1, c2); /*�e����uniform crossover�t�Xchildren c1 c2*/
                    Mutation(c1);
                    Mutation(c2);
                    children.push_back(c1);
                    children.push_back(c2);
                };
            }
            else /*��� : (greedy)�v�ɪkselect + mask crossover*/
            {
                while (children.size() < pop_size) /*�]���@���|�ͨ��child�ҥH\������children�Ӽƭp�����M��*/
                {
                    vector<int> c1(bit);            /*child1*/
                    vector<int> c2(bit);            /*child2*/
                    Select_Tournament();            /*������v�ɪk��X���parents p1 p2*/
                    Crossover_Mask(p1, p2, c1, c2); /*�����mask crossover�t�Xchildren c1 c2*/
                    Mutation(c1);
                    Mutation(c2);
                    children.push_back(c1);
                    children.push_back(c2);
                };
            };

            int best_parent_idx = max_element(fitness.begin(), fitness.end()) - fitness.begin(); /*Elitism : �d�U�̨�fitness parent��U�@�N*/
            children[0] = population[best_parent_idx];

            for (int i = 0; i < pop_size; ++i) /*update*/
            {
                Evaluation(children[i], fitness[i]);
                fitness_history.push_back(fitness[i]);
            }

            population = children;

            best_child_fit = *max_element(fitness.begin(), fitness.end());
        };

        Create_FitRecord("fitness_of_run_" + to_string(r + 1) + "_GA.txt", fitness_history); /*create .txt to record fitness in this run*/
        for (int j = 0; j < mnfes; ++j)
        {
            fitness_history_avg[j] += (double)fitness_history[j] / run; /*add fitness of every evaluations in this run to the summation*/
        }

        cout << best_child_fit << "\n"; /*��Xbest_fitness of each run*/
    }

    Create_FitRecord("fitness_average_GA.txt", fitness_history_avg); /*create .txt to record average fitness upon all runs*/

    ofstream plt("plot_GA.plt"); /*create .plt to generate plot by gnuplot*/
    plt << "set terminal png size 800, 600\n";
    plt << "set output 'results_OneMax_GeneticAlgo.png'\n";
    plt << "set title 'Average Convergence with GeneticAlgo on OneMax'\n";
    plt << "set xlabel 'Evaluation'\n";
    plt << "set ylabel 'Average Fitness'\n";
    plt << "set xrange [0:" << mnfes << "]\n";
    plt << "set yrange [0:" << bit << "]\n";
    plt << "plot 'fitness_average_GA.txt' using 1:2 with lines title 'Average with GeneticAlgo.png'\n";
    plt.close();
};

void algo_GA::Init() /*initialization*/
{
    nfes = 0; /*initialize times of evaluation*/
    population.clear();

    for (int p = 0; p < pop_size; ++p)
    {
        vector<int> ind(bit);         /*individual*/
        for (int b = 0; b < bit; ++b) /*randomly generate an individual*/
        {
            ind[b] = rand() % 2;
        }
        population.push_back(ind); /*��l�ѰʺA��J��population*/
    }
};

void algo_GA::Select_Roulette()
{
    /*���L�k��Xparents*/
    double sum = 0.0;
    for (int p = 0; p < pop_size; ++p)
    {
        sum += fitness[p];
    }

    auto spin = [&](double r) -> int
    {
        double acc = 0.0;
        for (int i = 0; i < pop_size; ++i)
        {
            acc += fitness[i] / sum;
            if (acc > r)
                return i;
        }
        return pop_size - 1;
    };
    int idx1 = spin((double)rand() / RAND_MAX);
    int idx2 = spin((double)rand() / RAND_MAX);

    while (idx1 == idx2)
    {
        idx1 = spin((double)rand() / RAND_MAX); /*�T�O���|���ۦPparents*/
    }

    p1 = population[idx1];
    p2 = population[idx2];
};

void algo_GA::Select_Tournament()
{
    /*�v�ɪk��Xparents*/
    int player_num = 3;
    auto tournament = [&]() -> vector<int>
    {
        int idx_best = rand() % pop_size;
        int score_best = OneMaxProblem(population[idx_best], bit);

        for (int i = 0; i < player_num; ++i)
        {
            int idx = rand() % pop_size;
            int score = OneMaxProblem(population[idx], bit);
            if (score > score_best)
            {
                idx_best = idx;
                score_best = score;
            }
        }
        return population[idx_best];
    };
    p1 = tournament();
    p2 = tournament();
    while (p1 == p2)
    {
        p1 = tournament();
    }
};

void algo_GA::Crossover_Unify(const vector<int> &p1, const vector<int> &p2, vector<int> &c1, vector<int> &c2)
{
    /*������crossover*/
    double cross_rate = 0.4; /*�]�wcross_rate*/

    for (int i = 0; i < bit; ++i)
    {
        double bit_rate = (double)rand() / RAND_MAX;
        if (bit_rate < cross_rate) /*do crossover*/
        {
            c1[i] = p2[i];
            c2[i] = p1[i];
        }
        else /*don't crossover*/
        {
            c1[i] = p1[i];
            c2[i] = p2[i];
        }
    }
};

void algo_GA::Crossover_Mask(const vector<int> &p1, const vector<int> &p2, vector<int> &c1, vector<int> &c2)
{
    /*���c���g����crossover*/
    vector<int> mask(bit);
    for (int i = 0; i < bit; ++i)
    {
        mask[i] = rand() % 2;
    }

    for (int j = 0; j < bit; ++j)
    {
        c1[j] = mask[j] ? p1[j] : p2[j];
        c2[j] = mask[j] ? p2[j] : p1[j];
    }
};

void algo_GA::Mutation(vector<int> &child)
{
    double mutation_rate = 0.0301 - (nfes*(15e-7)); /*adaptive mutation_rate*/

    for (int i = 0; i < bit; ++i)
    {
        double bit_rate = (double)rand() / RAND_MAX; /*each bit���ͤ���0~1���H����*/

        if (bit_rate < mutation_rate) /*�p�G��bit���H���Ƥp��mutation_rate*/
        {
            child[i] = 1 - child[i]; /*1��0 0��1*/
        }
    }
};

void algo_GA::Evaluation(const vector<int> &child, int &fitness)
{
    fitness = OneMaxProblem(child, bit);
    nfes++;
};

void algo_GA::Create_FitRecord(const string &filename, const vector<double> &content)
{
    ofstream record(filename);
    for (int i = 0; i < content.size(); ++i)
    {
        record << i + 1 << " " << content[i] << "\n";
    }
    record.close();
};