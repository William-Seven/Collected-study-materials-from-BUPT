#include "TestUtils.h"
#include <algorithm>
#include <ctime>
#include <random>

std::mt19937 gen(static_cast<unsigned int>(time(0)));  // 使用当前时间作为种子

// 生成随机数组
std::vector<int> TestUtils::generateRandomArray(int size, int maxValue) {
    std::uniform_int_distribution<> dis(0, maxValue);  // 设置范围为 0 到 maxValue
    std::vector<int> data(size);
    std::generate(data.begin(), data.end(), [&]() { return dis(gen); });
    return data;
}

// 生成有序数组
std::vector<int> TestUtils::generateSortedArray(int size) {
    std::vector<int> data(size);
    std::iota(data.begin(), data.end(), 0);
    return data;
}

// 生成逆序数组
std::vector<int> TestUtils::generateReversedArray(int size) {
    std::vector<int> data(size);
    std::iota(data.rbegin(), data.rend(), 0);
    return data;
}

// 生成重复数组
std::vector<int> TestUtils::generateRepeatedArray(int size, int value) {
    std::vector<int> data(size, value);
    return data;
}

// 验证数组是否已排序
bool TestUtils::validateSort(const std::vector<int>& data) {
    return std::is_sorted(data.begin(), data.end());
}
