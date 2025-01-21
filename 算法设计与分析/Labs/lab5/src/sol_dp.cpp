#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> pyramid;  // 存储金字塔的二维数组
vector<pair<int, int>> path;  // 存储路径的二维数组

// 使用高斯函数进行填充（最优填充方案）
double gaussian(double x, double y, double sigma) {
    return exp(-(x * x + y * y) / (2 * sigma * sigma));
}

double random_noise(double scale) {
    return (static_cast<double>(rand()) / RAND_MAX - 0.5) * scale;
}

void pyramid_gaussian_fill(int n, int k) {
    srand(time(0));
    pyramid.resize(n, vector<int>(n, 0));

    // 确定聚集块中心点的数量和位置
    int numClusters = k;
    vector<pair<double, double>> clusterCenters;

    // 随机选择k个中心点
    for (int i = 0; i < numClusters; ++i) {
        double centerX = static_cast<double>(rand()) / RAND_MAX * n;
        double centerY = static_cast<double>(rand()) / RAND_MAX * n;
        clusterCenters.push_back({centerX, centerY});
    }

    // 使用高斯分布函数填充聚集块中心点附近的值
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int value = 0;
            for (const auto& center : clusterCenters) {
                double g = gaussian(i - center.first, j - center.second, 3.0);  // Adjust sigma to control size
                value += static_cast<int>(g * 100);                             // Scale to 0-100
            }
            if (value > 100)
                value = 100;
            pyramid[i][j] = value;
        }
    }

    // 引入噪声让边缘不规则
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            pyramid[i][j] += static_cast<int>(random_noise(30));
            if (pyramid[i][j] < 0)
                pyramid[i][j] = 0;
            if (pyramid[i][j] > 100)
                pyramid[i][j] = 100;
        }
    }
}

// 将金字塔输出至文件
void print_pyramid_to_file(int n) {
    try {
        ofstream outfile("../pyramid_dp.txt");
        if (!outfile.is_open()) {
            cerr << "Failed to open file 'pyramid_dp.txt'" << endl;
            return;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - i; j++) {
                if (j != n - i - 1)
                    outfile << pyramid[i][j] << ",";
                else
                    outfile << pyramid[i][j];
            }
            outfile << endl;
        }
        outfile.close();
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return;
    }
}

// 动态规划求解最优路径
int dp_all(int n) {
    vector<vector<int>> values(n, vector<int>(n, 0));
    vector<vector<vector<pair<int, int>>>> path_all(n, vector<vector<pair<int, int>>>(n, vector<pair<int, int>>()));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - i; j++) {
            if (i == 0 && j == 0) {
                values[i][j] = pyramid[i][j];
                path_all[i][j].push_back({i, j});
            } else if (i == 0) {
                values[i][j] = values[i][j - 1] + pyramid[i][j];
                path_all[i][j] = path_all[i][j - 1];
                path_all[i][j].push_back({i, j});
            } else if (j == 0) {
                values[i][j] = values[i - 1][j] + pyramid[i][j];
                path_all[i][j] = path_all[i - 1][j];
                path_all[i][j].push_back({i, j});
            } else {
                values[i][j] = max(values[i - 1][j], values[i][j - 1]) + pyramid[i][j];
                if (values[i - 1][j] > values[i][j - 1]) {
                    path_all[i][j] = path_all[i - 1][j];
                    path_all[i][j].push_back({i, j});
                } else {
                    path_all[i][j] = path_all[i][j - 1];
                    path_all[i][j].push_back({i, j});
                }
            }
        }

    int ret = values[0][n - 1];
    for (int i = 1; i < n; i++)
        for (int j = n - 2; j >= 0; j--)
            if (values[i][j] > ret) {
                ret = values[i][j];
                path = path_all[i][j];
            }

    return ret;
}

// 打印路径至终端
void print_path() {
    for (int i = 0; i < path.size(); i++)
        cout << path[i].first << " " << path[i].second << endl;
}

// 打印路径至文件中
void print_path_to_file(int n) {
    ofstream outfile("../data/path_dp.txt");
    // cout<<"1"<<endl;
    if (!outfile.is_open()) {
        cerr << "Failed to open file 'path_dp.txt'" << endl;
        return;
    }
    // outfile << n << endl;
    for (int i = 0; i < path.size(); i++)
        outfile << path[i].first << " " << path[i].second << endl;

    cout << "path has been printed to file." << endl;
    outfile.close();
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
    int n = 100;  // 金字塔层数

    get_map_from_file("../data/pyramid_map.txt", n);

    int val = dp_all(n);  // 动态规划求解最优路径

    print_path();
    print_path_to_file(n);
    cout << val << endl;

    return 0;
}