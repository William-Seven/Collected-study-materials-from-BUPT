#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PAGE_SIZE 4       // 每页存储 PAGE_SIZE 条指令
#define ACCESS_COUNT 100  // 总共生成100个指令地址
#define MEMORY_SIZE 10    // 设置物理内存大小（页面数量）

// 生成内存访问串
void generate_page_access_sequence(int* page_access) {
    srand(time(NULL));  // 使用当前时间作为随机种子
    int m = 0;          // 初始地址

    for (int i = 0; i < ACCESS_COUNT; i++) {
        page_access[i] = m / PAGE_SIZE;  // 将内存地址映射到页面

        int rand_choice = rand() % 10;  // 随机生成下一条指令的访问模式
        if (rand_choice < 7) {
            m++;  // 顺序执行
        } else if (rand_choice < 8) {
            m = rand() % (m > 0 ? m : 1);  // 限制 m 的最小值为 0，防止在 m 为 0 时取值出错
        } else {
            if (m < ACCESS_COUNT - 1) {
                m = rand() % (ACCESS_COUNT - m - 1) + m + 1;  // 随机跳转在后地址范围随机选择
            } else {
                m++;
            }
        }
        m %= ACCESS_COUNT;  // 确保地址在 0 到 ACCESS_COUNT-1 范围内
    }

    // for (int i = 0; i < ACCESS_COUNT; i++)
    //     printf("%d, ", page_access[i]);
}

// 先进先出（FIFO）页面置换算法
int fifo_page_replacement(int* memory, int memory_size, int* pages) {
    int page_faults = 0;
    int ptr = 0;                                    // 指向下一个空位置
    memset(memory, -1, memory_size * sizeof(int));  // 初始化内存为空

    // 遍历所有页面访问
    for (int i = 0; i < ACCESS_COUNT; ++i) {
        bool hit = false;
        // 查找当前页面是否在内存中
        for (int j = 0; j < memory_size; ++j)
            if (memory[j] == pages[i]) {
                hit = true;
                break;
            }

        // 如果页面未命中，发生缺页
        if (!hit) {
            page_faults++;
            memory[ptr] = pages[i];         // 将页面载入内存
            ptr = (ptr + 1) % memory_size;  // 轮询指针，循环利用内存帧
        }
    }

    return page_faults;
}

// 最近最少使用（LRU）页面置换算法
int lru_page_replacement(int* memory, int memory_size, int* pages) {
    int page_faults = 0;
    memset(memory, -1, memory_size * sizeof(int));                // 初始化内存为空
    int* access_count = (int*)malloc(memory_size * sizeof(int));  // 存储每个内存页面的访问次数
    memset(access_count, 0, memory_size * sizeof(int));

    // 遍历所有页面访问
    for (int i = 0; i < ACCESS_COUNT; ++i) {
        int max_index = 0, max_count = 0;
        bool hit = false;

        // 查找页面是否已经在内存中
        for (int j = 0; j < memory_size; ++j) {
            if (memory[j] == pages[i]) {
                hit = true;
                max_index = j;
                break;
            }
            if (memory[j] == -1) {  // 找到空帧，直接放入
                max_index = j;
                break;
            }
            // 找到访问次数最多的页面，进行置换
            if (access_count[j] > max_count) {
                max_count = access_count[j];
                max_index = j;
            }
        }

        // 更新每个页面的访问计数
        for (int j = 0; j < memory_size; ++j)
            access_count[j]++;

        access_count[max_index] = 0;  // 重置当前页面的访问计数

        // 如果页面未命中，发生缺页
        if (!hit) {
            page_faults++;
            memory[max_index] = pages[i];  // 置换页面
        }
    }

    free(access_count);
    return page_faults;
}

// 最优页面置换算法（Optimal）
int optimal_page_replacement(int* memory, int memory_size, int* pages) {
    int page_faults = 0;
    memset(memory, -1, memory_size * sizeof(int));                   // 初始化内存为空
    int** next_access = (int**)malloc(ACCESS_COUNT * sizeof(int*));  // 存储每个页面的下次访问位置
    for (int i = 0; i < ACCESS_COUNT; ++i)
        next_access[i] = (int*)malloc(memory_size * sizeof(int));

    // 初始化next_access数组为ACCESS_COUNT，表示没有后续访问
    for (int i = 0; i < ACCESS_COUNT; ++i)
        for (int j = 0; j < memory_size; ++j)
            next_access[i][j] = ACCESS_COUNT;

    // 计算每个页面的未来访问位置
    for (int i = ACCESS_COUNT - 2; i >= 0; --i) {
        for (int j = 0; j < memory_size; ++j) {
            if (pages[i + 1] == j)
                next_access[i][j] = i + 1;
            else
                next_access[i][j] = next_access[i + 1][j];
        }
    }

    // 遍历所有页面访问
    for (int i = 0; i < ACCESS_COUNT; ++i) {
        int max_index = 0, max_count = 0;
        bool hit = false;

        // 查找页面是否在内存中
        for (int j = 0; j < memory_size; ++j) {
            if (memory[j] == pages[i]) {
                hit = true;
                break;
            }
            if (memory[j] == -1) {  // 找到空帧，直接放入
                max_index = j;
                break;
            }
            // 找到下次访问距离最远的页面，进行置换
            if (next_access[i][memory[j]] > max_count) {
                max_count = next_access[i][memory[j]];
                max_index = j;
            }
        }

        // 如果页面未命中，发生缺页
        if (!hit) {
            page_faults++;
            memory[max_index] = pages[i];  // 置换页面
        }
    }

    // 释放内存
    for (int i = 0; i < ACCESS_COUNT; ++i)
        free(next_access[i]);
    free(next_access);

    return page_faults;
}

// 计算缺页率
double calculate_page_fault_rate(int* memory, int memory_size, int* pages, int (*page_replacement_algo)(int*, int, int*)) {
    int page_faults = page_replacement_algo(memory, memory_size, pages);
    return (double)page_faults / ACCESS_COUNT;  // 缺页率 = 缺页次数 / 总访问次数
}

int main() {
    int pages[ACCESS_COUNT];
    generate_page_access_sequence(pages);  // 生成内存访问串且直接映射实际页地址保存

    int memory[MEMORY_SIZE];  // 存储页面的物理内存

    // 计算并输出不同页面置换算法的缺页率
    printf("FIFO: %.3f\n", calculate_page_fault_rate(memory, MEMORY_SIZE, pages, fifo_page_replacement));
    printf("LRU: %.3f\n", calculate_page_fault_rate(memory, MEMORY_SIZE, pages, lru_page_replacement));
    printf("OPTIMAL: %.3f\n", calculate_page_fault_rate(memory, MEMORY_SIZE, pages, optimal_page_replacement));

    return 0;
}
