#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>

// 定义排序算法类
class Algorithms {
   public:
    // 堆排序算法
    static void heapSort(std::vector<int>& data, int& comparisons, int& moves);

    // 归并排序算法
    static void mergeSort(std::vector<int>& data, int left, int right, int& comparisons, int& moves);

    // 快速排序算法
    static void quickSort(std::vector<int>& data, int low, int high, int& comparisons, int& moves);

    // 堆化函数，用于堆排序中的调整过程
    static void heapify(std::vector<int>& data, int n, int i, int& comparisons, int& moves);

    // 合并函数，用于归并排序的合并过程
    static void merge(std::vector<int>& data, int left, int mid, int right, int& comparisons, int& moves);

    // 分区函数，用于快速排序的划分过程
    static int partition(std::vector<int>& data, int low, int high, int& comparisons, int& moves);
};

#endif  // ALGORITHMS_H
