#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <algorithm>

const int MIN_LENGTH = 2;
const int MAX_LENGTH = 7;
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

void permute(std::string& word, int l, int r, std::set<std::string>& perms) {
    if (l == r) {
        perms.insert(word);
    } else {
        for (int i = l; i <= r; ++i) {
            std::swap(word[l], word[i]);
            permute(word, l + 1, r, perms);
            std::swap(word[l], word[i]);
        }
    }
}

int main() {
    std::ifstream fileInput = getFileInput();
    std::ofstream fileOutput = getFileOutput();

    std::string word;
    std::getline(fileInput, word);
    if (word.size() < MIN_LENGTH || word.size() > MAX_LENGTH) {
        std::cerr << "Invalid input" << std::endl;
        return 1;
    }

    std::set<std::string> perms;
    permute(word, 0, word.size() - 1, perms);

    for (const auto& perm : perms) {
        fileOutput << perm << std::endl;
    }

    return 0;
}