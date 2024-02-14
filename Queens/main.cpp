/*
 * �����: ������� �������
 * ������: ��-21
 *
 * 2.12. ����� (7)
 * ������� ������ � ������ ���������� �� ��������� ����� �������� N ? N  ������ N  ������  (1 ? N ? 12) ���, ����� ��� �� ��������� ���� �������.
 * ����� �������, ��� ������ ������ �� ������ ������������, ���������� � ����������.
 *
 * ���� �� ����� INPUT.TXT. � ������������ ������ �������� �������� N.
 *
 * ����� � ���� OUTPUT.TXT. ������� ��� ������� �������, ��������� ��������� ������������.
 * ����������� ����� ���������� �� 1 �� N. ��������� ������������ ��������� ���������� ������� �a�,�b�,�c� � �. �.
 * ���� � ������� ������ ��������� �� ����������� ������ ������� (����� �� ��������), � ���� ������� �� ����������� �����, ������� �� ������������.
 * � ��������� ������ �������� � ���������� ��������� �������.
 *
 * �������
 * ���� 1        ���� 2        ���� 3
 * 4             1             3
 * ����� 1       ����� 2       ����� 3
 * a2 b4 c1 d3   a1            0 positions
 * a3 b1 c4 d2   1 positions
 * 2 positions
 *
 * ����� ����������:  CLion 2023.2.1
 * ������ C++: C++17
 *
 * ���������:
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
#include <queue>

const std::string INPUT_FILE_NAME = "input.txt";
const std::string OUTPUT_FILE_NAME = "output.txt";
const std::string ALPHABET = "abcdefghijklmnopqrstuvwxyz";

std::vector<std::vector<int>> getSolutions(int N) {
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
                if (row == i || col == queens[i] || abs(row - i) == abs(col - queens[i])) {
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

void getAnswer() {
    std::ifstream fileInput = getFileInput();
    std::ofstream fileOutput = getFileOutput();
    int N = getAmountQueens(fileInput);

    std::vector<std::vector<int>> solutions = getSolutions(N);
    printSolutions(solutions, fileOutput);
}

int main() {
    try {
        getAnswer();
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
