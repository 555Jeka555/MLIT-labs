#include "maxMult.h"

std::vector<int> maxMult(int N) {
    std::vector<int> result;

    if (N <= 2) {
        result.push_back(N);
        return result;
    } else if (N == 3) {
        for (int i = 1; i < N; i++) {
            result.push_back(i);
        }
        return result;
    } else if (N == 4) {
        int sum = 0;
        for (int i = 1; i < N; i++) {
            sum += i;
            if (sum > N) {
                int diff = sum - N;
                if (diff == 1) {
                    result.erase(result.begin());
                } else {
                    result.erase(std::remove(result.begin(), result.end(), diff), result.end());
                }
            } else if (sum == N) {
                break;
            }
            result.push_back(i);
        }
        return result;
    }

    int sum = 0;
    for (int i = 2; i < N; i++) {
        sum += i;
        result.push_back(i);
        if (sum > N) {
            int diff = sum - N;
            if (diff == 1) {
                sum -= result.front();
                result.erase(result.begin());
            } else {
                sum -= diff;
                result.erase(std::remove(result.begin(), result.end(), diff), result.end());
            }
        } else if (sum == N) {
            break;
        }
    }

    return result;
}