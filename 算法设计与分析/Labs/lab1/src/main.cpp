#include <chrono>
#include <iostream>
#include "Algorithms.h"
#include "TestUtils.h"

int main() {
    int comparisons, moves;
    std::vector<int> data;

    // 测试用例
    auto testCases = {
        std::make_pair("Small Random Array", TestUtils::generateRandomArray(100, 100000)),
        std::make_pair("Small Sorted Array", TestUtils::generateSortedArray(100)),
        std::make_pair("Small Reversed Array", TestUtils::generateReversedArray(100)),
        std::make_pair("Large Random Array", TestUtils::generateRandomArray(10000, 100000)),
        std::make_pair("Large Sorted Array", TestUtils::generateSortedArray(10000)),
        std::make_pair("Large Reversed Array", TestUtils::generateReversedArray(10000)),
        std::make_pair("Repeated Array", TestUtils::generateRepeatedArray(100, 1))};

    for (const auto& testCase : testCases) {
        std::cout << "==========Testing " << testCase.first << "==========\n";

        // 堆排序
        data = testCase.second;
        comparisons = moves = 0;
        auto start = std::chrono::steady_clock::now();
        Algorithms::heapSort(data, comparisons, moves);
        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "Heap Sort - Comparisons: " << comparisons << ", Moves: " << moves
                  << ", Valid: " << (TestUtils::validateSort(data) ? "true" : "false")
                  << ", Time: " << duration << "us\n";

        // 归并排序
        data = testCase.second;
        comparisons = moves = 0;
        start = std::chrono::steady_clock::now();
        Algorithms::mergeSort(data, 0, data.size() - 1, comparisons, moves);
        end = std::chrono::steady_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "Merge Sort - Comparisons: " << comparisons << ", Moves: " << moves
                  << ", Valid: " << (TestUtils::validateSort(data) ? "true" : "false")
                  << ", Time: " << duration << "us\n";

        // 快速排序
        data = testCase.second;
        comparisons = moves = 0;
        start = std::chrono::steady_clock::now();
        Algorithms::quickSort(data, 0, data.size() - 1, comparisons, moves);
        end = std::chrono::steady_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "Quick Sort - Comparisons: " << comparisons << ", Moves: " << moves
                  << ", Valid: " << (TestUtils::validateSort(data) ? "true" : "false")
                  << ", Time: " << duration << "us\n\n";
    }

    return 0;
}
