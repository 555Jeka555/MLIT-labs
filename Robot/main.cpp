#include <iostream>
#include <fstream>
#include <vector>

const std::string INPUT_FILE_NAME = "input.txt";
const std::string OUTPUT_FILE_NAME = "output.txt";
const int MAX_X = 50;
const int MAX_Y = 50;

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

int main() {
    std::ifstream fileInput = getFileInput();
    std::ofstream fileOutput = getFileOutput();

    int X, Y;
    fileInput >> X >> Y;

    std::vector<std::vector<long long>> dp(MAX_X + 1, std::vector<long long>(MAX_Y + 1, 0));

    dp[0][0] = 1;

    for (int steps = 1; steps <= Y; ++steps) {
        for (int distance = 0; distance <= X; ++distance) {
            dp[distance][steps] = 0;

            if (distance > 0) {
                dp[distance][steps] += dp[distance - 1][steps - 1];
            }

            if (distance < X) {
                dp[distance][steps] += dp[distance + 1][steps - 1];
            }
        }
    }

    fileOutput << dp[X][Y] << std::endl;

    return 0;
}
