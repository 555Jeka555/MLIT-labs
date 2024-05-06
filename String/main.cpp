// Выполнил: Антышев Евгений
// Группа: ПС-21
//
// 13.4. Строка (4)
// В заданной строке символов из заглавных латинских букв найти подстроку, которая включает наибольшее количество букв,
// встречающихся в этой подстроке в единственном экземпляре. Если таких строк несколько, выдать наименьшую по алфавиту.
// Ввод из файла INPUT.TXT. В первой строке записана длина заданной строки N (1 ≤ N ≤106). Во второй строке -  N заглавных латинских букв,
// определяющих заданную строку.
// Вывод в файл OUTPUT.TXT. В единственную строку вывести подстроку с наибольшим количеством букв, встречающихся один раз.
// Ограничение. Объем используемой памяти до 1 Мгб.
// Примеры
// Ввод 1              Ввод 2           Ввод 3
// 5                   5                6
// ABBAC               OLYMP            DACDAC
// Вывод 1             Вывод 2          Вывод 3
// BAC                 OLYMP            ACD
//
// IDE: CLion 2023
// C++: C++ 17

#include <iostream>
#include <fstream>
#include <string>

const std::string INPUT_FILE_NAME = "input11.txt";
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

std::string findMaxUniqueSubstring(std::ifstream& fileInput) {
    std::string result;
    std::string current;

    char c;
    while (fileInput >> c) {
        auto cFinded = current.find(c);
        current += c;
        if (cFinded != -1)
        {
            current.erase(current.begin(), current.begin() + cFinded + 1);
        }
        if (current.length() > result.length() || (current.length() == result.length() && current <= result))
        {
            result = current;
        }

    }

    return result;
}

int main() {
    std::ifstream fileInput = getFileInput();
    std::ofstream fileOutput = getFileOutput();

    int N;
    fileInput >> N;

    // TODO Считать по символам вместо строки
    std::string result = findMaxUniqueSubstring(fileInput);

    fileOutput << result;

    return 0;
}
