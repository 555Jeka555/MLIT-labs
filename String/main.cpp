#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

const int MIN_LENGTH = 1;
const int MAX_LENGTH = 300;
const std::string INPUT_FILE_NAME = "input-big.txt";
const std::string OUTPUT_FILE_NAME = "output-big.txt";

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

string findMaxUniqueSubstring(const string& s) {
    int N = s.size();
    if (N == 0) {
        return "";
    }

    unordered_map<char, int> charCount;
    int left = 0;
    int maxLength = 0;
    string result = "";
    unordered_map<char, int> uniqueChars;

    for (int right = 0; right < N; right++) {
        charCount[s[right]]++;

        // Обновляем множество уникальных букв
        if (charCount[s[right]] == 1) {
            uniqueChars[s[right]] = right;
        }

        // Пока в подстроке есть более одного вхождения какой-либо буквы
        while (uniqueChars.size() != right - left + 1) {
            charCount[s[left]]--;
            if (charCount[s[left]] == 0) {
                uniqueChars.erase(s[left]);
            }
            left++;
        }

        // Проверяем, если текущая подстрока лучше предыдущей на основе условий задачи
        if (uniqueChars.size() > maxLength ||
           (uniqueChars.size() == maxLength && s.substr(left, right - left + 1) < result)) {
            maxLength = uniqueChars.size();
            result = s.substr(left, right - left + 1);
        }
    }

    return result;
}

int main() {
    std::ifstream fileInput = getFileInput();
    std::ofstream fileOutput = getFileOutput();

    int N;
    fileInput >> N;

    string s;
    fileInput >> s;

    string result = findMaxUniqueSubstring(s);

    fileOutput << result;
    
    return 0;
}
