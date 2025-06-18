# 比較 ExhaustiveSearch / HillClimbing / SimulatedAnnealing / GeneticAlgo 解 OneMax problem



## 1.基本說明

- Using C++
- Implement 30 minutes ExhaustiveSearch / HillClimbing / SimulatedAnnealing / GeneticAlgo / TabuSearch to solve OneMax problem



## 2.主要功能

### `ExhaustiveSearch`

- void RunALG(int bit) : 執行ES

- void Evaluation(const vector<int> &sol, int &value) : 計算新解的value
- void Reset() : 歸零窮舉次數


### `HillClimbing`

- void RunALG(int bit, int run, int iter) : 執行HC

- vector<int> vector<int> Init() : 產生一個隨機初始sol
- vector<int> Neighbor(const vector<int> &best_sol) : generate neighbour after flip one random bit from original solution
- void Evaluation(const vector<int> &sol, int &value) : 計算新解的value
- void Reset() : 每run歸零nfes次數

### `SimulatedAnnealing`

- void RunALG(int bit, int run, int iter) : 執行SA

- void Init(vector<int> &sol, int &value) : 隨機產生初始解
- vector<int> Neighbor(const vector<int> &sol) : 多點變異產生鄰居
- void Evaluation(const vector<int> &sol, int &value) : 計算新解的value
- void T_cooldown(double &temp) : 降低溫度
- void T_reheat(double &temp) : 升高溫度
- void Create_Vrecord(const string& filename, const vector<double>& content) : create.txt to record values

### `GeneticAlgo`

- void RunALG(int bit, int run, int iter, int pop_size) : 執行GA

- void Init() : 產生初始pop_size個解存入陣列population
- void Select_Roulette() : 輪盤法select
- void Select_Tournament() : 競賽法select
- void Mutation(vector<int> &child) : adaptive mutation
- void Crossover_Unify(const vector<int> &p1, const vector<int> &p2, vector<int> &c1, vector<int> &c2) : unify crossover，多元性大較易跳脫區域最佳解
- void Crossover_Mask(const vector<int> &p1, const vector<int> &p2, vector<int> &c1, vector<int> &c2) : mask crossover，適合具domain knowledge的問題 變動不大易卡在區域最佳解
- void Evaluation(const vector<int> &child, int &fitness) : 計算children的fitness
- void Create_FitRecord(const string &filename, const vector<double> &content) : create.txt to record fitness

### `TabuSearch`

- void RunALG(const int& _bit,
			const int& _run,
			const int& _iter,
			const int& _tabu_size,
			const int& _tweak_num) : 執行TabuSearch

- vector<int> Init() : 產生初始解並輸出，設定best_sol, best_fit初始值
- vector<int> Tweak(const vector<int> &origin_sol) : 微調origin_sol tweak_num次並輸出
- int Evaluation(const vector<int>& sol) : 計算sol的onemax fitness，輸出fitness
- void Create_Record(const string& filename, const vector<T>& content) : 產生紀錄內容的文字檔，因為實作在多種型別上所以使用template

## 3.Input

### command_line argument :

- 二進位位元數 | bit = 64(ES) / 100(HC / SA / GA)
- 回合數 | run = 30
- 單回合迭代次數 | iter = 1000
- 一世代人口數 | pop_size = 20 (GA)
- 演算法種類 | algo_type = ES / HC / SA / GA / TB
- (TabuSearch)         
Please type tabu_size = tabu_size   
Please type tweak_num = tweak_num


## 4.Output

### `HillClimbing`
- values_of_run_1~30_HC.txt
- values_average_HC.txt
- plot_HC.plt
- result_OneMax_HillClimbing.png


### `SimulatedAnnealing`
- values_of_run~30_SA.txt
- values_average_SA.txt
- plot_SA.plt
- result_OneMax_SimulatedAnnealing.png


### `GeneticAlgo`
- fitness_of_run_1~30.txt
- fitness_average.txt
- plot_GA.plt
- result_OneMax_GeneticAlgo.png

### `Tabusearch`
- fitness_of_run_1~30_TB_bit_size_tweak.txt
- fitness_average_TB_bit_size_tweak.txt
- plot_TB.plt
- result_onemax_TB_bit_size_tweak.png



## 5.執行方式

### `------------編譯------------` 
#### `VisualStudio`
1. 開啟 Visual Studio 專案 `OneMax.sln`
2. 按下 `Ctrl + F5` 開始編譯

#### `VSCode
1. 在 Windows cmd 或 PowerShell 中
2. 先到正確資料夾路徑
3. 輸入 : 

g++ main.cpp OneMax.cpp ExhaustiveSearch.cpp HillClimbing.cpp SimulatedAnnealing.cpp GeneticAlgo.cpp Tabu.cpp -o onemax.exe


### `------------執行------------`

1. 在 Windows cmd 或 PowerShell 中
2. 先到正確資料夾路徑
3. 輸入 :
.\onemax.exe bit run iter pop_size algo_type( ES / HC / SA / GA /TB )   
eg.    
.\onemax.exe 100 30 1000 1 HC
.\onemax.exe 100 30 1000 1 SA
.\onemax.exe 100 30 1000 20 GA
.\onemax.exe 64 1 1 1 ES
.\onemax.exe 10 30 5000 0 TB


### `------------出圖------------`

1. 安裝gnuplot
2. 在 Windows cmd 或 PowerShell 中
3. 先到正確資料夾路徑
4. 輸入 : 

gnuplot plot_HC.plt   
即可在資料夾中找到 result_OneMax_HillClimbing.png

gnuplot plot_SA.plt   
即可在資料夾中找到 result_OneMax_SimulatedAnnealing.png

gnuplot plot_GA.plt   
即可在資料夾中找到 result_OneMax_GeneticAlgo.png

gnuplot plot_TB.plt   
即可在資料夾中找到
result_onemax_TB_bit_size_tweak.png

##  6. 檔案結構
- onemax/  
 `main.cpp`  
 `ExhaustiveSearch.cpp` / `ExhaustiveSearch.h`  
 `GeneticAlgo.cpp` / `GeneticAlgo.h`   
 `HillClimbing.cpp` / `HillClimbing.h`
 `SimulatedAnnealing.cpp` / `SimulatedAnnealing.h`
 `Tabu.cpp` / `Tabu.h`
 `OneMax.cpp` / `OneMax.h`