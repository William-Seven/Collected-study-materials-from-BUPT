#include <bits/stdc++.h>

using namespace std;

const int INF = numeric_limits<int>::max();  // 表示正无穷

// 权重矩阵
int w[5][5] = {
    {INF, 50, 25, INF, 20},
    {50, INF, 30, 20, 25},
    {25, 30, INF, 15, 10},
    {INF, 20, 15, INF, 135},
    {20, 25, 10, 135, INF}};

int n = 5;                       // 顶点数
vector<int> x(n), x_best(n);     // 当前路径和最优路径
int cv = 0;                      // 当前路径长度
int v_best = INF;                // 最优路径长度
vector<bool> visited(n, false);  // 记录访问状态

void TspDFS(int i) {
    if (i == n) {                                // 递归结束条件
        if (w[x[i - 1]][0] < INF) {              // 剪枝2
            if (cv + w[x[i - 1]][0] < v_best) {  // 更新最优解
                cv += w[x[i - 1]][0];            // 回到起点
                cout << "Current path length: " << cv << endl;
                v_best = cv;
                x_best = x;
                for (int i = 0; i < n; ++i)
                    cout << x_best[i] + 1 << " ";  // 输出城市编号从1开始
                cout << x_best[0] + 1 << endl;     // 回到起点
                cv -= w[x[i - 1]][0];              // 回溯
            }
        }
    }

    for (int u = 0; u < n; u++) {
        if (!visited[u]) {                           // 如果城市u未被访问
            if (w[x[i - 1]][u] < INF) {              // 剪枝2
                if (cv + w[x[i - 1]][u] < v_best) {  // 剪枝1
                    cv += w[x[i - 1]][u];            // 更新当前路径长度
                    x[i] = u;                        // 选择城市u
                    visited[u] = true;               // 标记城市u为已访问
                    TspDFS(i + 1);                   // 递归搜索
                    visited[u] = false;              // 回溯
                    x[i] = -1;                       // 清除选择
                    cv -= w[x[i - 1]][u];            // 回溯
                }
            }
        }
    }
}

int main() {
    x[0] = 0;  // 起点为城市1（索引0）
    visited[0] = true;
    TspDFS(1);

    cout << "The shortest path length: " << v_best << endl;
    cout << "The shortest path: ";
    for (int i = 0; i < n; ++i)
        cout << x_best[i] + 1 << " ";  // 输出城市编号从1开始
    cout << x_best[0] + 1 << endl;     // 回到起点

    return 0;
}
