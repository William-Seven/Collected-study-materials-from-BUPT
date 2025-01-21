#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// 缓冲区和信号量定义
#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

// 信号量替代实现
typedef HANDLE sem_t;
int sem_init(sem_t* sem, int pshared, unsigned int value) {
    *sem = CreateSemaphore(NULL, value, BUFFER_SIZE, NULL);
    return *sem == NULL ? -1 : 0;
}
int sem_wait(sem_t* sem) {
    return WaitForSingleObject(*sem, INFINITE) == WAIT_FAILED ? -1 : 0;
}
int sem_post(sem_t* sem) {
    return ReleaseSemaphore(*sem, 1, NULL) == 0 ? -1 : 0;
}
int sem_destroy(sem_t* sem) {
    return CloseHandle(*sem) == 0 ? -1 : 0;
}

// 定义信号量
sem_t empty, full, mutex;

// 初始化随机数种子（使用高精度计时器）
void initialize_random_seed() {
    LARGE_INTEGER performance_counter;
    QueryPerformanceCounter(&performance_counter);  // 获取高精度计时器值
    srand((unsigned int)(performance_counter.QuadPart));
}

// 真随机数生成函数
int true_random(int min, int max) {
    return rand() % (max - min + 1) + min;  // 返回 [min, max] 范围内的随机数
}

// 生产者函数
void* producer_function(void* arg) {
    int id = *(int*)arg;
    initialize_random_seed();  // 每个线程初始化独立种子
    while (1) {
        int item = true_random(0, 99);  // 生成随机数
        Sleep(true_random(0, 3000));    // 模拟随机生产时间

        sem_wait(&empty);
        sem_wait(&mutex);

        // 添加到缓冲区
        buffer[in] = item;
        printf("Producer %d: Produced item %d at %d\n", id, item, in);
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&full);
    }
    return NULL;
}

// 消费者函数
void* consumer_function(void* arg) {
    int id = *(int*)arg;
    initialize_random_seed();  // 每个线程初始化独立种子
    while (1) {
        sem_wait(&full);
        sem_wait(&mutex);

        // 从缓冲区移除
        int item = buffer[out];
        printf("Consumer %d: Consumed item %d at %d\n", id, item, out);
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&empty);

        Sleep(true_random(0, 3000));  // 模拟随机消费时间
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <sleep_time> <num_producers> <num_consumers>\n", argv[0]);
        return -1;
    }

    int sleep_time = atoi(argv[1]);
    int num_producers = atoi(argv[2]);
    int num_consumers = atoi(argv[3]);

    pthread_t producers[num_producers], consumers[num_consumers];
    int producer_ids[num_producers], consumer_ids[num_consumers];

        // 初始化信号量
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    // 创建生产者线程
    for (int i = 0; i < num_producers; i++) {
        producer_ids[i] = i + 1;
        pthread_create(&producers[i], NULL, producer_function, &producer_ids[i]);
    }

    // 创建消费者线程
    for (int i = 0; i < num_consumers; i++) {
        consumer_ids[i] = i + 1;
        pthread_create(&consumers[i], NULL, consumer_function, &consumer_ids[i]);
    }

    // 主线程睡眠指定时间
    Sleep(sleep_time * 1000);
    printf("Main: Time up, exiting program.\n");

    // 取消线程
    for (int i = 0; i < num_producers; i++) {
        pthread_cancel(producers[i]);
    }
    for (int i = 0; i < num_consumers; i++) {
        pthread_cancel(consumers[i]);
    }

    // 销毁信号量
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
