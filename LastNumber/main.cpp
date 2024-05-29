#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

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

int lastDigitOfPower(int a, int n) {
    a = a % 10;

    vector<int> cycle;
    int current = a;

    while (true) {
        cycle.push_back(current);
        current = (current * a) % 10;
        if (current == a) {
            break;
        }
    }

    int cycle_length = cycle.size();

    int index = (n - 1) % cycle_length;

    return cycle[index];
}

int main() {
    std::ifstream fileInput = getFileInput();
    std::ofstream fileOutput = getFileOutput();
    int a, n;
    fileInput >> a >> n;

    int result = lastDigitOfPower(a, n);

    fileOutput << result << endl;

    return 0;
}
