#include "Algorithms.h"

// 堆排序实现
void Algorithms::heapSort(std::vector<int>& data, int& comparisons, int& moves) {
    int n = data.size();
    // 构建最大堆
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(data, n, i, comparisons, moves);

    // 提取元素并调整堆
    for (int i = n - 1; i >= 0; i--) {
        std::swap(data[0], data[i]);
        moves++;
        heapify(data, i, 0, comparisons, moves);
    }
}

// 调整堆函数
void Algorithms::heapify(std::vector<int>& data, int n, int i, int& comparisons, int& moves) {
    int largest = i;  // 最大元素索引
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // 比较左孩子
    if (left < n && data[left] > data[largest]) {
        largest = left;
        comparisons++;
    }
    // 比较右孩子
    if (right < n && data[right] > data[largest]) {
        largest = right;
        comparisons++;
    }
    // 如果需要交换
    if (largest != i) {
        std::swap(data[i], data[largest]);
        moves++;
        heapify(data, n, largest, comparisons, moves);  // 递归调整剩下的堆
    }
}

// 归并排序实现
void Algorithms::mergeSort(std::vector<int>& data, int left, int right, int& comparisons, int& moves) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(data, left, mid, comparisons, moves);
        mergeSort(data, mid + 1, right, comparisons, moves);
        merge(data, left, mid, right, comparisons, moves);
    }
}

// 合并函数
void Algorithms::merge(std::vector<int>& data, int left, int mid, int right, int& comparisons, int& moves) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<int> L(n1), R(n2);

    // 拷贝数据到临时数组
    for (int i = 0; i < n1; i++)
        L[i] = data[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = data[mid + 1 + j];

    int i = 0, j = 0, k = left;
    // 合并临时数组
    while (i < n1 && j < n2) {
        comparisons++;
        if (L[i] <= R[j]) {
            data[k++] = L[i++];
        } else {
            data[k++] = R[j++];
        }
        moves++;
    }

    // 拷贝剩余元素
    while (i < n1) {
        data[k++] = L[i++];
        moves++;
    }
    while (j < n2) {
        data[k++] = R[j++];
        moves++;
    }
}

// 快速排序实现
void Algorithms::quickSort(std::vector<int>& data, int low, int high, int& comparisons, int& moves) {
    if (low < high) {
        int pi = partition(data, low, high, comparisons, moves);
        quickSort(data, low, pi - 1, comparisons, moves);
        quickSort(data, pi + 1, high, comparisons, moves);
    }
}

// 分区函数
int Algorithms::partition(std::vector<int>& data, int low, int high, int& comparisons, int& moves) {
    int pivot = data[high];  // 基准
    int i = low;

    for (int j = low; j < high; j++) {
        comparisons++;
        if (data[j] < pivot) {
            std::swap(data[i++], data[j]);
            moves++;
        }
    }
    std::swap(data[i], data[high]);
    moves++;
    return i;  // 返回分区点
}