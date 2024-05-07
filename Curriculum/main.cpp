// Выполнил: Антышев Евгений
// Группа: ПС-21
//
// Учебный план включает перечень дисциплин. Задан список пар дисциплин.
// Отдельная пара показывает, что вторая дисциплина должна изучаться после  первой.
// Составить список дисциплин учебного плана в порядке их изучения. В том случае, когда задание некорректно,
// т.е. в списке пар имеются циклы, выдать хотя бы один из них.
//
// Ввод из файла INPUT.TXT. В первой строке задается число пар дисциплин N (1 ≤ N ≤ 300).
// В каждой из следующих N строк указываются через пробел  два  натуральных  числа  Xi , Yi (Xi , Yi ≤ 1000),
// определяющих номера дисциплин.  Первая дисциплина должна изучаться раньше второй.
//
// Вывод в файл OUTPUT.TXT. В первой строке вывести Yes  либо No – возможность расположения в списке дисциплин
// в порядке их изучения. При наличии такой возможности во второй строке выводится через пробел искомый список.
// Если задание некорректно, т.е. имеется цикл, то во второй строке выдается список номеров, образующих цикл.
// Первый и последний номера в этом списке должны совпадать.
// Примеры
// Ввод 1           Ввод 2
// 7                8
// 1 2              1 2
// 1 3              1 3
// 2 5              2 5
// 3 4              3 4
// 4 2              4 2
// 3 2              3 2
// 6 4              6 4
//                  5 3
// Вывод 1          Вывод 2
// Yes              No
// 1 6 3 4 2 5      2 5 3 4 2
//
// IDE: CLion 2023
// C++: C++ 17

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <unordered_set>

const int MIN_LENGTH = 1;
const int MAX_LENGTH = 300;
const std::string INPUT_FILE_NAME = "test/input5.txt";
const std::string OUTPUT_FILE_NAME = "output.txt";

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

bool hasCycleUtil(int current,
                  std::vector<std::vector<int>>& graph,
                  std::vector<bool>& visited,
                  std::vector<bool>& recursion_stack,
                  std::vector<int>& recursion_vertex) {
    visited[current] = true;
    recursion_stack[current] = true;

    for (int next : graph[current]) {
        if (!visited[next] && hasCycleUtil(next, graph, visited, recursion_stack, recursion_vertex) || recursion_stack[next]) {

            if (recursion_vertex.empty()) {
                for (int i = next; i < recursion_stack.size(); i++) {
                    if (recursion_stack[i]) {
                        recursion_vertex.push_back(i);
                    }
                }
            }

            return true;
        }
    }

    recursion_stack[current] = false;
    return false;
}

bool hasCycle(int N, std::vector<std::vector<int>>& graph) {
    std::vector<bool> visited(N + 1, false);
    std::vector<bool> recursion_stack(N + 1, false);
    std::vector<int> recursion_vertex;

    for (int i = 1; i <= N; ++i) {
        if (!visited[i] && hasCycleUtil(i, graph, visited, recursion_stack, recursion_vertex)) {
            return true;
        }
    }

    return false;
}

void topologicalSort(int current, std::vector<std::vector<int>>& graph, std::vector<bool>& visited, std::vector<int>& result) {
    visited[current] = true;
    for (int next : graph[current]) {
        if (!visited[next]) {
            topologicalSort(next, graph, visited, result);
        }
    }

    result.push_back(current);
}

char findDuplicate(const std::string& str) {
    std::unordered_set<char> seen;

    for (char ch : str) {
        if (ch == ' ') {
            continue;
        }

        if (seen.count(ch)) {
            return ch;
        } else {
            seen.insert(ch);
        }
    }

    return '\0';
}

int main() {
    std::ifstream fileInput = getFileInput();
    std::ofstream fileOutput = getFileOutput();

    int N, M = INT_MIN;
    fileInput >> N;

    if (N < MIN_LENGTH || N > MAX_LENGTH) {
        std::cerr << "Invalid input" << std::endl;
        return 1;
    }

    std::vector<std::vector<int>> graph(MAX_LENGTH + 1);

    for (int i = 1; i <= N; ++i) {
        int X, Y;
        fileInput >> X >> Y;
        M = std::max(M, std::max(X, Y));
        graph[X].push_back(Y);
    }

    if (hasCycle(N, graph)) {
        fileOutput << "No" << std::endl;
        std::vector<bool> visited(N + 1, false);
        std::vector<bool> recursion_stack(N + 1, false);
        std::vector<int> recursion_vertex;
        for (int i = 1; i <= N; ++i) {
            if (!visited[i] && hasCycleUtil(i, graph, visited, recursion_stack, recursion_vertex)) {
                std::string result = std::to_string(i) + " ";

                int current = graph[i][0];
                int start = current;
                bool isFirst = true;
                bool isIndexCycle = true;

                while (current != i) {
                    if (!isFirst && current == start) {
                        size_t pos = result.find(' ');

                        if (pos != std::string::npos) {
                            std::string newStr = result.substr(pos + 1);
                            result = newStr;
                        }

                        result += std::to_string(current) + " ";
                        isIndexCycle = false;
                        break;
                    }
                    result += std::to_string(current) + " ";

                    char duplicate = findDuplicate(result);
                    if (duplicate != '\0') {
                        size_t start_pos = result.find(duplicate);

                        if (start_pos != std::string::npos) {
                            size_t end_pos = result.find(duplicate, start_pos + 1);

                            if (end_pos != std::string::npos) {
                                result = result.substr(start_pos, end_pos - start_pos + 1);
                            }
                        }
                        isIndexCycle = false;
                        break;
                    }

                    if (graph[current].empty()) {
                        break;
                    }

                    int nextIndex = 0;
                    while (true) {
                        bool isFind = false;

                        for (auto j : recursion_vertex) {
                            if (graph[current][nextIndex] == j) {
                                current = graph[current][nextIndex];
                                isFind = true;
                                break;
                            }
                        }
                        if (isFind) {
                            break;
                        }

                        nextIndex++;
                    }
                    isFirst = false;
                }

                if (isIndexCycle) {
                    result += std::to_string(i);
                }

                fileOutput << result << std::endl;

                break;
            }
        }
    } else {
        fileOutput << "Yes" << std::endl;

        std::vector<bool> visited(M + 1, false);
        std::vector<int> result;
        for (int i = 1; i <= M; ++i) {
            if (!visited[i]) {
                topologicalSort(i, graph, visited, result);
            }
        }
        std::reverse(result.begin(), result.end());
        for (int num : result) {
            fileOutput << num << " ";
        }
    }

    fileInput.close();
    fileOutput.close();

    return 0;
}
