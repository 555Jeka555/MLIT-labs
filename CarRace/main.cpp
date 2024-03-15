#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>

const std::string INPUT_FILE_NAME = "input1.txt";
const std::string OUTPUT_FILE_NAME = "output.txt";

void GetInputsFromInputFile(
        int &amountCanister,
        int &lengthLap,
        std::vector<int> &pointsCanister,
        std::vector<int> &mileagesReserve,
        std::vector<std::pair<int, int>> &diffReserve
) {
    std::ifstream inputFile(INPUT_FILE_NAME);
    std::string line;
    std::getline(inputFile, line);
    std::istringstream iss(line);
    int num1, num2;
    if (iss >> num1 >> num2) {
        amountCanister = num1;
        lengthLap = num2;
    }

    std::getline(inputFile, line);
    std::istringstream iss1(line);
    int number;
    while (iss1 >> number) {
        pointsCanister.push_back(number);
    }

    std::getline(inputFile, line);
    std::istringstream iss2(line);
    while (iss2 >> number) {
        mileagesReserve.push_back(number);
    }

    for (int i = 0; i < amountCanister; ++i) {
        if (i + 1 < amountCanister) {
            diffReserve.emplace_back(pointsCanister[i + 1] - pointsCanister[i], mileagesReserve[i]);
        } else {
            diffReserve.emplace_back(lengthLap - pointsCanister[i] + pointsCanister[0], mileagesReserve[i]);
        }
    }
}

int main() {
    int amountCanister;
    int lengthLap;

    std::vector<int> pointsCanister;
    std::vector<int> mileagesReserve;
    std::vector<std::pair<int, int>> diffReserve;

    GetInputsFromInputFile(amountCanister, lengthLap, pointsCanister, mileagesReserve, diffReserve);

    int startCanister = mileagesReserve[0];
    int maxDistance = 0;

    for (int i = 0; i < mileagesReserve.size(); i++) {
        int mileageReserve = mileagesReserve[i];
        int currentDistance = 0;
        int additionalReserve = 0;
        for (int j = 0; j < diffReserve.size(); j++) {
            int distance = diffReserve[j].first;

            if (j + 1 < diffReserve.size()) {
                additionalReserve = diffReserve[j + 1].second;
            }

            if (mileageReserve >= distance) {
                currentDistance += distance;
                mileageReserve -= distance;
                mileageReserve += additionalReserve;

            } else {
                currentDistance += mileageReserve;
                break;
            }
        }

        if (currentDistance >= maxDistance) {
            startCanister = i + 1;
            maxDistance = currentDistance;
        }

        std::rotate(diffReserve.begin(), diffReserve.begin() + 1, diffReserve.end());
    }

    std::cout << startCanister << " " << maxDistance << std::endl;

    return 0;
}
