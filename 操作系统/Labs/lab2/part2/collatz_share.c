#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>  // 用于内存映射函数，如 mmap() 和 shm_open()
#include <sys/wait.h>
#include <unistd.h>

#define SHM_NAME "/collatz_shm"  // 共享内存对象的名称
#define SHM_SIZE 4096            // 共享内存大小，定义为 4096 字节

void generate_collatz_sequence(int n, char* shared_memory) {
    char buffer[256];  // 用于存储每个数字转换后的字符串
    while (n != 1) {
        sprintf(buffer, "%d, ", n);     // 将当前数字转换为字符串并存入 buffer
        strcat(shared_memory, buffer);  // 将 buffer 中的内容拼接到共享内存中
        if (n % 2 == 0) {
            n /= 2;
        } else {
            n = 3 * n + 1;
        }
    }
    strcat(shared_memory, "1\n");
}

int main() {
    int n;
    printf("Please enter a positive integer: ");
    scanf("%d", &n);

    if (n <= 0) {
        fprintf(stderr, "Please provide a positive integer greater than 0.\n");
        return 1;
    }

    // 创建共享内存对象
    // SHM_NAME: 共享内存对象的名称
    // O_CREAT | O_RDWR: 表示如果不存在则创建，并允许读写
    // 0666: 共享内存对象的权限（读写）
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        return 1;
    }

    // 设置共享内存大小
    if (ftruncate(shm_fd, SHM_SIZE) == -1) {
        perror("ftruncate");
        return 1;
    }

    // 将共享内存映射到进程的地址空间
    // 0: 建议的内存起始地址，0 表示让系统选择合适的地址
    // SHM_SIZE: 映射的大小
    // PROT_READ | PROT_WRITE: 设置权限为读写
    // MAP_SHARED: 共享映射，意味着子父进程都可访问此内存
    // shm_fd: 共享内存的文件描述符
    // 0: 偏移量，0 表示从头开始映射
    char* shared_memory = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shared_memory == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    // 清空共享内存，确保没有残留数据
    memset(shared_memory, 0, SHM_SIZE);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        generate_collatz_sequence(n, shared_memory);
        exit(0);
    } else {
        wait(NULL);
        printf("Collatz sequence for %d: %s", n, shared_memory);

        // 删除共享内存对象，防止资源泄露
        if (shm_unlink(SHM_NAME) == -1) {
            perror("shm_unlink");
            return 1;
        }

        printf("Child process has finished. Parent process exiting.\n");
    }

    return 0;
}