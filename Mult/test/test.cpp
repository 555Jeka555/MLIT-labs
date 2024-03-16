#include <gtest/gtest.h>
#include "../src/maxMult.h"

TEST (mult, mult_small_success)
{
    int N = 1;
    std::vector<int> mult = maxMult(N);
    std::vector<int> expected = {1};
    int sum = std::accumulate(expected.begin(), expected.end(), 0);
    EXPECT_EQ(expected, mult);
    EXPECT_EQ(N, sum);

    N = 2;
    mult = maxMult(N);
    expected = {2};
    sum = std::accumulate(expected.begin(), expected.end(), 0);
    EXPECT_EQ(expected, mult);
    EXPECT_EQ(N, sum);

    N = 3;
    mult = maxMult(N);
    expected = {1, 2};
    sum = std::accumulate(expected.begin(), expected.end(), 0);
    EXPECT_EQ(expected, mult);
    EXPECT_EQ(N, sum);

    N = 4;
    mult = maxMult(N);
    expected = {1, 3};
    sum = std::accumulate(expected.begin(), expected.end(), 0);
    EXPECT_EQ(expected, mult);
    EXPECT_EQ(N, sum);
}

TEST (mult, mult_small_loop_success)
{
    int N = 5;
    std::vector<int> mult = maxMult(N);
    std::vector<int> expected = {2, 3};
    int sum = std::accumulate(expected.begin(), expected.end(), 0);
    EXPECT_EQ(expected, mult);
    EXPECT_EQ(N, sum);

    N = 6;
    mult = maxMult(N);
    expected = {2, 4};
    sum = std::accumulate(expected.begin(), expected.end(), 0);
    EXPECT_EQ(expected, mult);
    EXPECT_EQ(N, sum);

    N = 7;
    mult = maxMult(N);
    expected = {3, 4};
    sum = std::accumulate(expected.begin(), expected.end(), 0);
    EXPECT_EQ(expected, mult);
    EXPECT_EQ(N, sum);

    N = 8;
    mult = maxMult(N);
    expected = {3, 5};
    sum = std::accumulate(expected.begin(), expected.end(), 0);
    EXPECT_EQ(expected, mult);
    EXPECT_EQ(N, sum);

    N = 9;
    mult = maxMult(N);
    expected = {2, 3, 4};
    sum = std::accumulate(expected.begin(), expected.end(), 0);
    EXPECT_EQ(expected, mult);
    EXPECT_EQ(N, sum);

    N = 10;
    mult = maxMult(N);
    expected = {2, 3, 5};
    sum = std::accumulate(expected.begin(), expected.end(), 0);
    EXPECT_EQ(expected, mult);
    EXPECT_EQ(N, sum);
}

TEST (mult, mult_middle_loop_success)
{
    int N = 100;
    std::vector<int> mult = maxMult(N);
    std::vector<int> expected = {2, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    int sum = std::accumulate(expected.begin(), expected.end(), 0);
    EXPECT_EQ(expected, mult);
    EXPECT_EQ(N, sum);

    N = 50;
    mult = maxMult(N);
    expected = {2, 3, 5, 6, 7, 8, 9, 10};
    sum = std::accumulate(expected.begin(), expected.end(), 0);
    EXPECT_EQ(expected, mult);
    EXPECT_EQ(N, sum);

    N = 53;
    mult = maxMult(N);
    expected = {3, 4, 5, 6, 7, 8, 9, 11};
    sum = std::accumulate(expected.begin(), expected.end(), 0);
    EXPECT_EQ(expected, mult);
    EXPECT_EQ(N, sum);
}

TEST (mult, mult_max_loop_success)
{
    int N = 10000;
    std::vector<int> mult = maxMult(N);
    std::vector<int> expected = {2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,
                                 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
                                 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70,
                                 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92,
                                 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
                                 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129,
                                 130, 131, 132, 133, 134, 135, 136, 137,138, 139, 140, 141};
    int sum = std::accumulate(expected.begin(), expected.end(), 0);
    EXPECT_EQ(expected, mult);
    EXPECT_EQ(N, sum);
}

GTEST_API_ int main (int argc, char **argv)
{
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}