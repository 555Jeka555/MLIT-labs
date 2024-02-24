/*
 * Автор: Антышев Евгений
 * Группа: ПС-21
 *
 * 2.12. Ферзи (7)
 * Методом поиска в ширину расставить на шахматной доске размером N ? N  клеток N  ферзей  (1 ? N ? 12) так, чтобы они не атаковали один другого.
 * Иными словами, они должны стоять на разных горизонталях, вертикалях и диагоналях.
 *
 * Ввод из файла INPUT.TXT. В единственной строке задается значение N.
 *
 * Вывод в файл OUTPUT.TXT. Вывести все искомые позиции, используя шахматные обозначениях.
 * Горизонтали доски нумеруются от 1 до N. Вертикали обозначаются строчными лаьтнскими буквами ‘a‘,‘b‘,‘c‘ и т. д.
 * Поля в позиции должны следовать по возрастанию номера столбца (буквы по алфавиту), а сами позиции по возрастанию строк, которые их представляют.
 * В последней строке сообщить о количестве найденных позиций.
 *
 * Примеры
 * Ввод 1        Ввод 2        Ввод 3
 * 4             1             3
 * Вывод 1       Вывод 2       Вывод 3
 * a2 b4 c1 d3   a1            0 positions
 * a3 b1 c4 d2   1 positions
 * 2 positions
 *
 * Среда разработки:  CLion 2023.2.1
 * Версия C++: C++17
 *
 * Источники:
 * https://forallx.ru/posts/n-queens-problem
 * https://www.youtube.com/watch?v=4iDv8Zu8L3I
 * https://www.youtube.com/watch?v=TrJW0o6C_pw
 * https://www.youtube.com/watch?v=bF5d0tiGiJA
 *
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

const std::string INPUT_FILE_NAME = "input.txt";
const std::string OUTPUT_FILE_NAME = "output.txt";
const std::string ALPHABET = "abcdefghijklmnopqrstuvwxyz";

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

int getAmountQueens(std::ifstream &fileInput) {
    std::string line;
    int N = 0;
    if (std::getline(fileInput, line)) {
        N = std::stoi(line);
        if (N < 1 || N > 12) {
            throw std::runtime_error("Invalid size");
        }
    }
    return N;
}

std::string printQueens(std::vector<std::pair<int, int>> queens) {
    std::string answer;
    for (auto queen: queens) {
        answer += ALPHABET[queen.second];
        answer += std::to_string(queen.first + 1);
        answer += " ";
    }
    return answer;
}

std::vector<std::vector<std::pair<int, int>>> getSolutionsByBFS(int N) {
    std::vector<std::vector<std::pair<int, int>>> solutions;
    std::queue<std::pair<int, std::vector<std::pair<int, int>>>> queue;

    for (int col = 0; col < N; col++) {
        std::vector<std::pair<int, int>> queens;
        queens.push_back({0, col});
        queue.push({0, queens});
    }

    while (!queue.empty()) {
        int startRow = queue.front().first;
        int nextRow = startRow + 1;
        std::vector<std::pair<int, int>> queens = queue.front().second;
        queue.pop();

        if (queens.size() == N) {
            std::sort(queens.begin(), queens.end(), [](const auto& a, const auto& b) {
                return a.second < b.second;
            });
            solutions.push_back(queens);
            continue;
        }

        for (int col = 0; col < N; col++) {
            bool isSafe = true;

            for (auto queen: queens) {
                if (queen.second == col
                    || abs(nextRow - queen.first) == abs(col - queen.second)
                        ) {
                    isSafe = false;
                    break;
                }
            }
            if (isSafe) {
                std::vector<std::pair<int, int>> newQueens = queens;
                newQueens.emplace_back(nextRow, col);
                queue.push({nextRow, newQueens});
            }
        }
    }

    return solutions;
}

std::vector<std::vector<int>> getSolutionsByVector(int N) {
    std::vector<std::vector<int>> solutions;
    std::queue<std::pair<int, std::vector<int>>> queue;
    queue.push({0, {}});

    while (!queue.empty()) {
        int row = queue.front().first;
        std::vector<int> queens = queue.front().second;

        queue.pop();

        if (row == N) {
            solutions.push_back(queens);
            continue;
        }

        for (int col = 0; col < N; col++) {
            bool isSafe = true;
            for (int i = 0; i < queens.size(); i++) {
                if (col == queens[i] || abs(row - i) == abs(col - queens[i])) {
                    isSafe = false;
                    break;
                }
            }
            if (isSafe) {
                std::vector<int> newQueens = queens;

                newQueens.push_back(col);
                queue.push({row + 1, newQueens});
            }
        }
    }

    return solutions;
}

void printSolutions(const std::vector<std::vector<int>> &solutions, std::ofstream &fileOutput) {
    int N = solutions.size();
    for (int i = 0; i < N; i++) {
        std::string answer;
        std::vector<int> solution = solutions[i];
        for (int col = 0; col < solution.size(); col++) {
            int row = solution[col];
            answer += ALPHABET[col];
            answer += std::to_string(row + 1);
            answer += " ";
        }
        answer += "\n";
        fileOutput << answer;
    }
    std::string amountPosition = std::to_string(N) + " positions";
    fileOutput << amountPosition;
}

void printSolutionsByPair(std::vector<std::vector<std::pair<int, int>>> solutionsByBFS, std::ofstream &fileOutput) {
    for (const auto &solution: solutionsByBFS) {
        std::string answer = printQueens(solution);
        answer += "\n";
        fileOutput << answer;
    }
    std::string amountPosition = std::to_string(solutionsByBFS.size()) + " positions";
    fileOutput << amountPosition;
}

bool compare(const std::vector<std::pair<int, int>>& a, const std::vector<std::pair<int, int>>& b) {
    if (a.empty() && !b.empty()) {
        return true;
    }
    if (b.empty() && !a.empty()) {
        return false;
    }
    if (a.empty() && b.empty()) {
        return false;
    }
    return a[0].first < b[0].first;
}

void getAnswer() {
    std::ifstream fileInput = getFileInput();
    std::ofstream fileOutput = getFileOutput();
    int N = getAmountQueens(fileInput);

//    std::vector<std::vector<int>> solutionsByVector = getSolutionsByVector(N);
//    printSolutions(solutionsByVector, fileOutput);

    std::vector<std::vector<std::pair<int, int>>> solutionsByBFS = getSolutionsByBFS(N);
    std::sort(solutionsByBFS.begin(), solutionsByBFS.end(), compare);
    printSolutionsByPair(solutionsByBFS, fileOutput);
//    printSolutions(solutionsByBFS, fileOutput);
}

int main() {
    try {
        getAnswer();
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
