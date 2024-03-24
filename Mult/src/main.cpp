// Выполнил: Антышев Евгений
// Группа: ПС-21
//
// Среди всех наборов различных целых положительных чисел, сумма которых
// равна заданному числу N (1 ≤ N ≤ 10000), найдите тот,
// который имеет максимальное произведение входящих в него чисел.
// Ввод из файла INPUT.TXT. В единственной строке вводится N.
// Вывод в файл OUTPUT.TXT. В единственной строке выдаются слагаемые через пробел.
// Примеры
//        Ввод 1      Ввод 2
//        8           100
//        Вывод 1     Вывод 2
//        3 5         2 3 5 6 7 8 9 10 11 12 13 14
//
// IDE: CLion 2023.2.1
// C++: C++20

#include "maxMult.h"

const std::string INPUT_FILE_NAME = "input.txt";
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

int getN(std::ifstream &fileInput) {
    std::string line;
    int N = 0;
    if (std::getline(fileInput, line)) {
        N = std::stoi(line);
        if (N < 1 || N > 10000) {
            throw std::runtime_error("Invalid size");
        }
    }
    return N;
}

int main() {
    std::ifstream fileInput = getFileInput();
    std::ofstream fileOutput = getFileOutput();
    int N = getN(fileInput);

    std::vector<int> result = maxMult(N);

    for (int i = 0; i < result.size(); ++i) {
        fileOutput << result[i] << " ";
        std::cout << result[i] << " ";
    }

    return 0;
}
