// Выполнил: Антышев Евгений
// Группа: ПС-21
// 15.4. Дерево игры (5)
// Игра для двух игроков определяется ее деревом. Соперники делают ходы по очереди. Первый игрок начинает игру. Игра кончается или вничью, или победой одного из игроков. Листья дерева этой игры могут иметь значения, равные одному из трех чисел: +1 - победа первого игрока, -1 - победа второго игрока, 0 - ничья. Ваша задача - определить, кто выиграет, если оба противника следуют правильной стратегии.
// Ввод из файла INPUT.TXT. Узлы дерева пронумерованы последовательными целыми числами. Корень дерева всегда имеет номер 1. Первая строка входного файла содержит целое N - число узлов в дереве игры. Следующая N - 1 строка описывает узлы - одна строка для каждого узла (за исключением первого). Вторая строка содержит описание второго узла дерева, третья - третьего узла и т.д. Если узел является листом, первый символ строки - L, затем идёт пробел, затем номер родительского узла, ещё пробел и результат игры (+1 - победа первого игрока, -1 - победа второго, 0 - ничья). Если узел внутренний, то строка содержит N - первый символ, затем пробел и номер родительского узла.
// Вывод в файл OUTPUT.TXT. Выводится +1, если выигрывает первый игрок, -1, если второй, и 0 - в случае ничейного исхода.
// Ограничения: 2 ≤  N ≤ 1000, время 1 с.
// Примеры
// Ввод 1    Ввод 2
// 7         7
// N 1       N 1
// N 1       N 1
// L 2 -1    L 2 -1
// L 2 +1    L 2 +1
// L 3 +1    L 3 +1
// L 3 +1    L 3 0
// Вывод 1   Вывод 2
// +1        0
// Ввод 3 (см. рисунок)
// 18
// N 1
// N 1
// N 2
// L 2 +1
// N 3
// L 3 +1
// L 3 +1
// L 4 -1
// L 4 +1
// N 4
// N 6
// L 6 -1
// L 6 -1
// L 11 -1
// L 11 +1
// L 12 +1
// L 12 -1
// Вывод 3
// +1
//
// IDE: CLion 2023
// C++: C++ 17

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

const std::string INPUT_FILE_NAME = "input-big.txt";
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


struct Node {
    char type;
    int parent;
    int result;
};

int minimax(vector<Node>& nodes, int position, bool isMaximizingPlayer) {
    Node& currentNode = nodes[position];

    if (currentNode.type == 'L') {
        return currentNode.result;
    }

    if (isMaximizingPlayer) {
        int maxEval = INT_MIN;
        for (int i = 2; i < nodes.size(); i++) {
            Node& node = nodes[i];

            if (node.parent == position) {
                int eval = minimax(nodes,i, false);
                maxEval = max(maxEval, eval);
            }
        }
        return maxEval;
    } else {
        int minEval = INT_MAX;
        for (int i = 2; i < nodes.size(); i++) {
            Node& node = nodes[i];

            if (node.parent == position) {
                int eval = minimax(nodes,i, true);
                minEval = min(minEval, eval);
            }
        }
        return minEval;
    }
}

int main() {
    std::ifstream fileInput = getFileInput();
    std::ofstream fileOutput = getFileOutput();

    int N;
    fileInput >> N;

    vector<Node> nodes(N + 1);

    nodes[1].type = 'N';
    nodes[1].parent = 0;

    for (int i = 2; i < nodes.size(); ++i) {
        char type;
        int parent;
        fileInput >> type >> parent;

        nodes[i].type = type;
        nodes[i].parent = parent;

        if (nodes[i].type == 'L') {
            int result;
            fileInput >> result;
            nodes[i].result = result;
        }
    }

    int winner = minimax(nodes, 1, true);

    fileOutput << winner << endl;

    return 0;
}
