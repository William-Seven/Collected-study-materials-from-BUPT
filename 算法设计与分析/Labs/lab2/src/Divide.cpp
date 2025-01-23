#include <chrono>  // 用于计算执行时间
#include <iomanip>
#include <iostream>
using namespace std;
using namespace std::chrono;

const int MAX_SIZE = 10010;
int schedule[MAX_SIZE][MAX_SIZE];
int byePlayers[MAX_SIZE];  // 记录轮空选手的数组
int numPlayers;

// 打印赛程安排
void printSchedule(int num) {
    if (num % 2 == 0) {  // 偶数个选手
        for (int i = 1; i <= num; i++) {
            for (int j = 1; j <= num; j++) {
                if (j == 1)
                    cout << setw(4) << schedule[i][j] << ":";
                else
                    cout << setw(4) << schedule[i][j];
            }
            cout << endl;
        }
    } else {  // 奇数个选手
        for (int i = 1; i <= num; i++) {
            for (int j = 1; j <= num + 1; j++) {
                if (j == 1)
                    cout << setw(4) << schedule[i][j] << ":";
                else if (schedule[i][j] == num + 1)
                    cout << setw(4) << "/";
                else
                    cout << setw(4) << schedule[i][j];
            }
            cout << endl;
        }
    }
    cout << endl;
}

// 偶数选手的复制逻辑
void handleEven(int num) {
    int half = num / 2;
    for (int i = 1; i <= half; i++) {
        for (int j = 1; j <= half; j++) {
            schedule[i][j + half] = schedule[i][j] + half;  // 右上角
            schedule[i + half][j] = schedule[i][j + half];  // 左下角
            schedule[i + half][j + half] = schedule[i][j];  // 右下角
        }
    }
}

// 奇数选手的复制逻辑
void handleOdd(int num) {
    int half = num / 2;
    // 计算轮空选手对应情况
    for (int i = 1; i <= half; i++) {
        byePlayers[i] = half + i;
        byePlayers[half + i] = byePlayers[i];
    }
    for (int i = 1; i <= half; i++) {
        for (int j = 1; j <= half + 1; j++) {
            if (schedule[i][j] > half) {  // 当前选手轮空
                schedule[i][j] = byePlayers[i];
                schedule[half + i][j] = (byePlayers[i] + half) % num;
            } else {  // 非轮空情况
                schedule[half + i][j] = schedule[i][j] + half;
            }
        }
        for (int j = 2; j <= half; j++) {
            schedule[i][half + j] = byePlayers[i + j - 1];
            schedule[byePlayers[i + j - 1]][half + j] = i;
        }
    }
}

// 复制赛程
void copySchedule(int num) {
    if (num / 2 > 1 && (num / 2) % 2 == 1)
        handleOdd(num);
    else
        handleEven(num);
}

// 递归生成赛程
void generateSchedule(int num) {
    if (num == 1) {  // 基础情况
        schedule[1][1] = 1;
        return;
    }
    if (num % 2 == 1) {
        generateSchedule(num + 1);  // 奇数人，补充一个轮空
        return;
    }
    generateSchedule(num / 2);  // 递归生成一半人数的赛程
    copySchedule(num);          // 根据一半赛程复制生成完整赛程
}

int main() {
    cout << "Enter the number of players: ";
    cin >> numPlayers;

    // 开始计时
    auto startTime = high_resolution_clock::now();

    generateSchedule(numPlayers);

    // 停止计时
    auto endTime = high_resolution_clock::now();

    // 输出结果
    if (numPlayers <= 30) {
        cout << "Generated schedule:\n";
        printSchedule(numPlayers);
    }

    // 计算并输出执行时间
    auto duration = duration_cast<microseconds>(endTime - startTime);
    cout << "Execution time: " << duration.count() << " microseconds" << endl;

    return 0;
}
