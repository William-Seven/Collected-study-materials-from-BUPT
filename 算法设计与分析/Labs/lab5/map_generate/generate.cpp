#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> pyramid;  // 存储金字塔的二维数组

// 使用随机数值填写金字塔
void pyramid_random_fill(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            pyramid[i][j] = rand() % 100;
        }
    }
}

// 使用正态模拟的方式填充金字塔
void pyramid_normal_fill(int n, int k) {
    // 定义正态分布参数
    double mean = 50.0;    // 均值
    double stddev = 10.0;  // 标准差

    // 创建一个正态分布的随机数生成器
    default_random_engine generator;
    normal_distribution<double> distribution(mean, stddev);
    uniform_int_distribution<int> point_distribution(0, n - 1);

    pyramid.assign(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - i; ++j) {
            double value = distribution(generator);
            int clampedValue = static_cast<int>(round(value));
            if (clampedValue < 0)
                clampedValue = 0;
            if (clampedValue > 100)
                clampedValue = 100;
            pyramid[i][j] = clampedValue;
        }
    }

    cout << "Pyramid has been filled with values:" << endl;
}

double gaussian(double x, double y, double sigma) {
    return exp(-(x * x + y * y) / (2 * sigma * sigma));
}

double random_noise(double scale) {
    return (static_cast<double>(rand()) / RAND_MAX - 0.5) * scale;
}

// 使用高斯函数进行填充（最优填充方案）
void pyramid_gaussian_fill(int n, int k) {
    srand(time(0));
    pyramid.resize(n, vector<int>(n, 0));

    // 确定聚集块中心点的数量和位置
    int numClusters = k;
    vector<pair<double, double>> clusterCenters;

    // 随机选择k个中心点
    for (int i = 0; i < numClusters; ++i) {
        double centerX = static_cast<double>(rand()) / RAND_MAX * n / 2;
        double centerY = static_cast<double>(rand()) / RAND_MAX * (n - centerX);
        clusterCenters.push_back({centerX, centerY});
    }

    // 使用高斯分布函数填充聚集块中心点附近的值
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int value = 0;
            for (const auto& center : clusterCenters) {
                double g = gaussian(i - center.first, j - center.second, 3.0);  // 调整σ值以控制聚集块的形状和强度
                value += static_cast<int>(g * 100);                             // 范围在0-100之间
            }
            if (value > 100)
                value = 100;
            pyramid[i][j] = value;
        }
    }

    // 引入噪声进行空白位置填充
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            pyramid[i][j] += static_cast<int>(random_noise(65));
            if (pyramid[i][j] < 0)
                pyramid[i][j] = 0;
            if (pyramid[i][j] > 100)
                pyramid[i][j] = 100;
        }
    }
}

// DEBUG 输出金字塔至终端
void print_pyramid(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            if (j != n - i - 1)
                cout << pyramid[i][j] << ",";
            else
                cout << pyramid[i][j];
        }
        cout << endl;
    }
    cout << "pyramid has been printed to terminal." << endl;
}

// 将金字塔输出至文件
void print_pyramid_to_file(int n) {
    try {
        ofstream outfile("pyramid.txt");
        if (!outfile.is_open()) {
            cerr << "Failed to open file 'pyramid.txt'" << endl;
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

int main() {
    int n = 100;
    int k = 12;

    pyramid_gaussian_fill(n, k);

    print_pyramid_to_file(n);
    return 0;
}