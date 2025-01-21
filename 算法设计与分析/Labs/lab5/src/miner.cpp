#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> pyramid;
vector<pair<int, int>> path;

// 贪心算法
int miner_greedy(int n) {
    int x = 0, y = 0;
    int total_value = 0;
    while (x + y < n - 1) {
        if (x + 1 < n - y && y + 1 < n - x) {
            if (pyramid[x + 1][y] > pyramid[x][y + 1]) {
                total_value += pyramid[x + 1][y];
                path.push_back(make_pair(x + 1, y));
                x++;
            } else {
                total_value += pyramid[x][y + 1];
                path.push_back(make_pair(x, y + 1));
                y++;
            }
        }
    }
    cout << "path find successfully" << endl;
    return total_value;
}

// 打印路径至终端
void print_path() {
    for (int i = 0; i < path.size(); i++) {
        cout << path[i].first << " " << path[i].second << endl;
    }
}

// 打印路径至文件中
void print_path_to_file(int n) {
    ofstream outfile("../data/path_greedy.txt");
    // cout<<"1"<<endl;
    if (!outfile.is_open()) {
        cerr << "Failed to open file 'path.txt'" << endl;
        return;
    }
    // outfile << n << endl;
    for (int i = 0; i < path.size(); i++) {
        outfile << path[i].first << " " << path[i].second << endl;
    }
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
    int n = 100;
    get_map_from_file("../data/pyramid_map.txt", n);
    int val = miner_greedy(n);
    cout << val << endl;
    print_path_to_file(n);
    return 0;
}