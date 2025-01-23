#include <iostream>
using namespace std;

void makeTable(int num) {
    int days = num - (num + 1) % 2;  // 比赛的天数
    cout << "\nTournament Schedule:\n";
    for (int i = 0; i < days; i++) {
        cout << "Day " << (i + 1) << ": ";
        int len = num - 1;
        for (int j = 0; j < num / 2; j++) {
            cout << ((i + j) % num + 1) << " vs "
                 << ((i + j + len) % num + 1);
            if (j < num / 2 - 1)
                cout << ", ";  // 添加逗号分隔
            len -= 2;
        }
        cout << endl;  // 换行，进入下一天
    }
}

int main() {
    int n;
    cout << "Enter the number of participants: ";
    cin >> n;

    makeTable(n);
    return 0;
}
