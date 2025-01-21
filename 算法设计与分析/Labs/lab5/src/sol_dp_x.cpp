#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> pyramid;  // 存储金字塔的二维数组
vector<pair<int, int>> path;  // 存储路径的二维数组

// 打印路径至终端
void print_path() {
    for (int i = 0; i < path.size(); i++)
        cout << path[i].first << " " << path[i].second << endl;
}

// 打印路径至文件中
void print_path_to_file(int n, int k) {
    stringstream ss;
    ss << "../data/path_dp_x_"<< k <<"_right.txt";
    ofstream outfile(ss.str());
    // cout<<"1"<<endl;
    if (!outfile.is_open()) {
        cerr << "Failed to open file 'path_dp.txt'" << endl;
        return;
    }
    // outfile << n << endl;
    for (int i = 0; i < path.size(); i++)
        outfile << path[i].first << " " << path[i].second << endl;

    // cout << "path has been printed to file." << endl;
    outfile.close();
}

// 探测范围为 x 的动态规划算法
// 传入起始点的坐标
int dp_x(int start_i, int start_j, int n, int x) {
    // 先判断最大探测范围还剩多少
    if (start_i + start_j + x > n - 1)
        x = n - 1 - start_i - start_j;

    int ret = 0;
    vector<vector<int>> values(n, vector<int>(n, 0));

    for (int i = start_i; i < start_i + x + 1; i++)
        for (int j = start_j; j < start_j + x + 1; j++) {
            if (i == start_i && j == start_j) {
                values[i][j] = pyramid[i][j];
            } else if (i == start_i) {
                values[i][j] = values[i][j - 1] + pyramid[i][j];
            } else if (j == start_j) {
                values[i][j] = values[i - 1][j] + pyramid[i][j];
            } else {
                values[i][j] = max(values[i - 1][j], values[i][j - 1]) + pyramid[i][j];
            }
        }

    for (int i = start_i; i < start_i + x + 1; i++)
        for (int j = start_j + x; j >= start_j; j--)
            if (values[i][j] > ret) {
                ret = values[i][j];
            }

    return ret;
}

// 矿工前进过程
int step(int n, int x) {
    int ret = pyramid[0][0];

    // 起始位置
    int current_i = 0;
    int current_j = 0;

    while (current_i + current_j < n) {
        int left_value = -1;
        int right_value = -1;
        // 先处理右边的局部最优
        if (current_i < n && current_j + 1 < n) {
            right_value = dp_x(current_i, current_j + 1, n, x - 1);
        }
        // 再处理左边的局部最优
        if (current_i + 1 < n && current_j < n) {
            left_value = dp_x(current_i + 1, current_j, n, x - 1);
        }

        // 说明到达金字塔底部
        if (right_value == -1 && left_value == -1)
            break;

        // 右边的局部最优比左边大，向右下方走一步
        if (right_value > left_value) {
            current_j += 1;                          // 向右走一步
            ret += pyramid[current_i][current_j];    // 累加这一步的价值
            path.push_back({current_i, current_j});  // 记录这一步的路径
        } else {
            current_i += 1;                          // 向左走一步
            ret += pyramid[current_i][current_j];    // 累加这一步的价值
            path.push_back({current_i, current_j});  // 记录这一步的路径
        }
    }

    return ret;
}

// 从文件中读取地图
void get_map_from_file(string filename, int n) {
    ifstream map_file(filename);

    string line;
    while (getline(map_file, line)) {  // 逐行读取文件
        if (line.empty())
            continue;  // 忽略空行

        stringstream ss(line);
        vector<int> row;
        row.assign(n, 0);  // 设置行长度为n
        string item;
        int row_num = 0;

        while (getline(ss, item, ',')) {  // 按逗号分割每行的数据
            if (!item.empty()) {
                try {
                    row[row_num++] = stoi(item);
                } catch (const invalid_argument& e) {
                    cerr << "Invalid argument: " << e.what() << endl;
                    throw;
                } catch (const out_of_range& e) {
                    cerr << "Out of range: " << e.what() << endl;
                    throw;
                }
            }
        }

        if (!row.empty()) {
            pyramid.push_back(row);  // 将当前行添加到金字塔中
        }
    }

    map_file.close();
}

int main() {
    int n = 100;  // 金字塔的大小
    // int x = 10;   // 探测范围
    // 打开文件输出 val 的值
    ofstream outfile("../data/val_results_x_left.txt");

    get_map_from_file("../data/pyramid_map.txt", n);

    // 遍历 x 的值从 1 到 100
    for (int x = 1; x <= 100; ++x) {
        path.clear();
        int val = step(n, x);

        // print_path();
        // print_path_to_file(n, x);

        // 将 val 的值写入文件
        outfile << val << endl;
        // cout << val << endl;
    }

    // 关闭文件
    outfile.close();

    return 0;
}