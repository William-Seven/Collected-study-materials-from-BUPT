#ifndef TESTUTILS_H
#define TESTUTILS_H

#include <string>
#include <vector>

// 定义测试工具类
class TestUtils {
   public:
    // 生成随机数组
    static std::vector<int> generateRandomArray(int size, int maxValue);

    // 生成有序数组
    static std::vector<int> generateSortedArray(int size);

    // 生成逆序数组
    static std::vector<int> generateReversedArray(int size);

    // 生成重复数组
    static std::vector<int> generateRepeatedArray(int size, int value);

    // 验证数组是否排序
    static bool validateSort(const std::vector<int>& data);
};

#endif  // TESTUTILS_H
