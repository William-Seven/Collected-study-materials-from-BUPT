#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 2048

int src1[N][N];
int src2[N][N];
int dst1[N][N];
int dst2[N][N];

void copyij(int src[2048][2048], int dst[2048][2048])
{
    int i, j;
    for (i = 0; i < 2048; i++)
        for (j = 0; j < 2048; j++)
            dst[i][j] = src[i][j];
}

void copyji(int src[2048][2048], int dst[2048][2048])
{
    int i, j;
    for (j = 0; j < 2048; j++)
        for (i = 0; i < 2048; i++)
            dst[i][j] = src[i][j];
}

int main()
{
    clock_t start_time, end_time; // 存储时间值
    double elapsed_time_ij, elapsed_time_ji;

    for (int i = 0; i < 2048; i++)
        for (int j = 0; j < 2048; j++)
            src2[i][j] = src1[i][j] = i + j;

    // 测试copyij 函数
    start_time = clock();
    copyij(src1, dst1);
    end_time = clock();
    elapsed_time_ij = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // 测试 copyji 函数
    start_time = clock();
    copyji(src2, dst2);
    end_time = clock();
    elapsed_time_ji = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // 输出运行时间
    printf("Time taken by copyij: %f seconds\n", elapsed_time_ij);
    printf("Time taken by copyji: %f seconds\n", elapsed_time_ji);

    // 比较运行时间
    if (elapsed_time_ij < elapsed_time_ji)
        printf("copyij is faster.\n");
    else
        printf("copyji is faster.\n");

    system("pause");
    return 0;
}