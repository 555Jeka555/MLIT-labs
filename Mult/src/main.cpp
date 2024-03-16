#include "maxMult.h"

int main() {
    int N;
    std::cin >> N;

    std::vector<int> result = maxMult(N);

    for (int i = 0; i < result.size(); ++i) {
        std::cout << result[i] << " ";
    }

    return 0;
}
