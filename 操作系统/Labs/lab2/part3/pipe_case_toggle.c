#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 256  // 定义缓冲区大小为 256 字节

void toggle_case(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (isupper(str[i])) {
            str[i] = tolower(str[i]);
        } else if (islower(str[i])) {
            str[i] = toupper(str[i]);
        }
    }
}

int main() {
    // pipe1: 父进程到子进程的管道, pipe2: 子进程到父进程的管道
    int pipe1[2], pipe2[2];
    pid_t pid;
    char message[BUFFER_SIZE];           // 用户输入的消息
    char modified_message[BUFFER_SIZE];  // 子进程修改后的消息

    printf("Please enter a message: ");
    fgets(message, BUFFER_SIZE, stdin);
    message[strcspn(message, "\n")] = '\0';  // 去掉换行符

    // 创建两个管道
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        close(pipe1[1]);  // 关闭 pipe1 的写端，因为子进程只需要读取
        close(pipe2[0]);  // 关闭 pipe2 的读端，因为子进程只需要写入

        // 从父进程读取消息
        read(pipe1[0], modified_message, BUFFER_SIZE);
        close(pipe1[0]);  // 读取完后关闭 pipe1 的读端

        toggle_case(modified_message);

        // 将修改后的消息发送回父进程
        write(pipe2[1], modified_message, strlen(modified_message) + 1);
        close(pipe2[1]);  // 发送完消息后关闭 pipe2 的写端

        exit(0);
    } else {
        close(pipe1[0]);  // 关闭 pipe1 的读端，因为父进程只需要写入
        close(pipe2[1]);  // 关闭 pipe2 的写端，因为父进程只需要读取

        // 将消息发送给子进程
        write(pipe1[1], message, strlen(message) + 1);
        close(pipe1[1]);  // 发送完后关闭 pipe1 的写端

        // 等待子进程结束并读取修改后的消息
        wait(NULL);
        read(pipe2[0], modified_message, BUFFER_SIZE);
        close(pipe2[0]);

        printf("Modified message: %s\n", modified_message);
    }

    return 0;
}