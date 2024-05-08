// Выполнил: Антышев Евгений
// Группа: ПС-21
//
// 1.2. Колорадский жук (4)
// Прямоугольный садовый участок длиной M ×N метров (1≤ M, N ≤5) разбит на квадраты со стороной 1 метр.
// На этом участке вскопана грядка картошки. Грядкой является связанное множество квадратов.
// Иными словами, из любого квадрата этой грядки можно попасть в любой другой квадрат этой же грядки,
// последовательно переходя по грядке из квадрата в квадрат через их общую сторону.
// В некоторых квадратах грядки растут кусты картошки. Колорадский жук прилетел на один из кустов.
// Съев все листья, он переходит через общую сторону к какому-либо соседнему свежему кусту той же грядки.
// Жук не возвращается к тому кусту, на котором он уже был, и не приходит в те квадраты, где картошка не посажена.
// Определить наибольшее количество кустов картошки, которые сможет съесть колорадский жук.
//
// Ввод. В первой строке файла INPUT.TXT находятся числа M и N через пробел. Далее идут M строк по N символов.
// Квадраты грядки с кустами картошки обозначаются символами '#', свободные квадраты – символами '.'.
//
// Вывод. В единственной строке файла OUTPUT.TXT вывести одно число - наибольшее возможное количество съеденных кустов картошки.
// Пример
// Ввод
// 3 4
// ####
// .#..
// .###
// Вывод
// 7
//
// IDE: CLion 2023
// C++: C++ 17

#include <iostream>
#include <fstream>
#include <stack>
#include <vector>

const std::string INPUT_FILE_NAME = "input.txt";
const std::string OUTPUT_FILE_NAME = "output.txt";
const char BUSH_CHAR = '#';
const char DOT_CHAR = '.';

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

struct Point {
    int x;
    int y;
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

bool isBush(const std::vector<std::vector<char>> &map, Point point) {
    return !(point.y < 0
            || point.x < 0
            || point.y >= map.size()
            || point.x >= map[0].size())
           && map[point.y][point.x] == BUSH_CHAR;
}

bool isPointInStack(Point point, const std::stack<Point>& stack) {
    bool isPointInStack = false;
    std::stack<Point> tempStack = stack;
    while (!tempStack.empty()) {
        Point top = tempStack.top();
        tempStack.pop();

        if (point.x == top.x && point.y == top.y) {
            isPointInStack = true;
            break;
        }
    }

    return isPointInStack;
}

int getCountByPoint(const std::vector<std::vector<char>>& tempMap, Point startPoint) {
    auto map = tempMap;

    std::stack<Point> stack{};
    stack.push(startPoint);
    int count = 0;
    while (!stack.empty()) {
        auto topPoint = stack.top();

        Point upPoint = {topPoint.x + 1, topPoint.y};
        if (!isPointInStack(upPoint, stack) && isBush(map, upPoint)) {
            stack.push(upPoint);
            continue;
        }

        Point rightPoint = {topPoint.x, topPoint.y + 1};
        if (!isPointInStack(rightPoint, stack) && isBush(map, rightPoint)) {
            stack.push(rightPoint);
            continue;
        }

        Point downPoint = {topPoint.x - 1, topPoint.y};
        if (!isPointInStack(downPoint, stack) && isBush(map, downPoint)) {
            stack.push(downPoint);
            continue;
        }

        Point leftPoint = {topPoint.x, topPoint.y - 1};
        if (!isPointInStack(leftPoint, stack) && isBush(map, leftPoint)) {
            stack.push(leftPoint);
            continue;
        }

        map[topPoint.y][topPoint.x] = DOT_CHAR;
        if (count < stack.size()) {
            count = (int)stack.size();
        }
        stack.pop();
    }

    return count;
}

int main() {
    std::ifstream fileInput = getFileInput();
    std::ofstream fileOutput = getFileOutput();

    std::vector<std::vector<char>> map;
    std::string line;
    std::getline(fileInput, line);
    while (std::getline(fileInput, line)) {
        std::vector<char> vec;
        for (const auto &ch : line) {
            vec.push_back(ch);
        }
        map.push_back(vec);
    }

    int maxCount = 0;
    for (int row = 0; row < map.size(); ++row) {
        for (int col = 0; col < map[row].size(); ++col) {

            if (map[row][col] == BUSH_CHAR) {
                int count = getCountByPoint(map, Point(col,row));

                maxCount = std::max(maxCount, count);
            }

        }
    }

    fileOutput << maxCount << std::endl;
}