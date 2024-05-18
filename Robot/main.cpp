// Выполнил: Антышев Евгений
// Группа: ПС-21
//
// 3.2. Робот 1 (5).
// Робот находится на расстоянии X шагов от цели. За один ход он продвигается либо к цели,
// либо в противоположном направлении. Если он достигает цели, то немедленно останавливается.
// Найти количество способов достижения цели ровно за Y шагов.
//
// Ввод из файла INPUT.TXT. В единственной строке находятся X и Y (1 ≤ X, Y ≤ 50).
//
// Вывод в файл OUTPUT.TXT. В единственной строке вывести количество способов достижения цели.
//
// Пример
// Ввод 1     Ввод 2
// 3 3        3 5
// Вывод 1    Вывод 2
// 1          3
//
// IDE: CLion 2023
// C++: C++ 17

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

const std::string INPUT_FILE_NAME = "input9.txt";
const std::string OUTPUT_FILE_NAME = "output.txt";
const int MAX_X = 50;
const int MAX_Y = 50;

std::ifstream getFileInput() {
    std::ifstream fileInput(INPUT_FILE_NAME);
    if (!fileInput.is_open()) {
        throw std::runtime_error("Error to open first INPUT file");
    }
    return fileInput;
}

std::ofstream getFileOutput() {
    std::ofstream fileOutputClear(OUTPUT_FILE_NAME, std::ios::trunc);
    if (!fileOutputClear.is_open()) {
        throw std::runtime_error("Error to open first OUTPUT file");
    }
    fileOutputClear.close();

    std::ofstream fileOutput(OUTPUT_FILE_NAME, std::ios::app);
    if (!fileOutput.is_open()) {
        throw std::runtime_error("Error to open first OUTPUT file");
    }
    return fileOutput;
}


long long findWaysTarget(int x, int y, vector<vector<long long>>& memo) {
    if (x == 0) {
        return (y == 0) ? 1 : 0;
    }

    if (y == 0) {
        return 0;
    }

    if (memo[x][y] != -1) {
        return memo[x][y];
    }

    long long ways = findWaysTarget(x - 1, y - 1, memo) + findWaysTarget(x + 1, y - 1, memo);

    memo[x][y] = ways;

    return ways;
}

int findWaysRecurent(int X, int Y) {
    vector<vector<int>> dp(X + 1, vector<int>(Y + 1, 0));

    dp[0][0] = 1;

    for (int steps = 1; steps <= Y; ++steps) {
        for (int distance = 0; distance <= X; ++distance) {

            if (distance > 0) {
                dp[distance][steps] += dp[distance - 1][steps - 1];
            }

            if (distance < X) {
                dp[distance][steps] += dp[distance + 1][steps - 1];
            }
        }
    }

    return dp[X][Y];
}

int main() {
    std::ifstream fileInput = getFileInput();
    std::ofstream fileOutput = getFileOutput();

    int X, Y;
    fileInput >> X >> Y;

    time_t startTime = std::clock();

    vector<vector<long long>> memo(MAX_X * 4, vector<long long>(MAX_Y * 4, -1));

    long long result = findWaysTarget(X, Y, memo);
//    int result = findWaysRecurent(X, Y);

    fileOutput << result << std::endl;

    std::cout << (double) (std::clock() - startTime) / (double) 1000;

    return 0;
}
