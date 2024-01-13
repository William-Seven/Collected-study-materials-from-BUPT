#include<iostream>
#include<map>
#include<vector>
#include<string>
#include<algorithm>
#define ls(o) (o << 1)
#define rs(o) (ls(o) | 1)
#define ini 0x3f3f3f3f
using namespace std;

const int N = 1e6 + 10;
int n, q;
vector<string> saveadds;
struct node {
	int op, id;
	string l, r;
}act[N];
int l[N], r[N], mx[N], mn[N], lazy[N], sum[N];

void pushup(int id) {
    mx[id] = max(mx[ls(id)], mx[rs(id)]);
    mn[id] = min(mn[ls(id)], mn[rs(id)]);
    sum[id] = sum[ls(id)] + sum[rs(id)];
}
//建树
void build(int id, int L, int R) {
    l[id] = L;
    r[id] = R;
    mn[id] = ini;
    mx[id] = -ini;
    lazy[id] = ini;
    if (L >= R) 
        return;
    int mid = L + R >> 1;
    build(ls(id), L, mid);
    build(rs(id), mid + 1, R);
    pushup(id);
}

void pushdown(int id) {
    if (lazy[id] != ini) {
        sum[ls(id)] = r[ls(id)] - l[ls(id)] + 1;
        sum[rs(id)] = r[rs(id)] - l[rs(id)] + 1;
        mx[ls(id)] = lazy[id];
        mx[rs(id)] = lazy[id];
        mn[ls(id)] = lazy[id];
        mn[rs(id)] = lazy[id];
        lazy[ls(id)] = lazy[id];
        lazy[rs(id)] = lazy[id];
        lazy[id] = ini;
    }
}
//查找数组中出现s的位置
int find(string s) {
    return lower_bound(saveadds.begin(), saveadds.end(), s) - saveadds.begin() + 1;
}

int judgemin(int id, int L, int R) {
    if (l[id] >= L && r[id] <= R) 
        return mn[id];
    pushdown(id);
    int mid = l[id] + r[id] >> 1;
    int ans = ini;
    if (mid >= L) 
        ans = judgemin(ls(id), L, R);
    if (mid + 1 <= R) 
        ans = min(ans, judgemin(rs(id), L, R));
    return ans;
}
//更新节点信息
void update(int id, int L, int R, int val) {
    if (l[id] >= L && r[id] <= R) {
        sum[id] = r[id] - l[id] + 1;
        mx[id] = val;
        mn[id] = val;
        lazy[id] = val;
        return;
    }
    pushdown(id);
    int mid = l[id] + r[id] >> 1;
    if (mid >= L) 
        update(ls(id), L, R, val);
    if (mid + 1 <= R) 
        update(rs(id), L, R, val);
    pushup(id);
}
//判断该地址是否已经全部分配给id 
int judgesum(int id, int L, int R) {
    if (l[id] >= L && r[id] <= R) 
        return sum[id];
    pushdown(id);
    int mid = l[id] + r[id] >> 1;
    long long ans = 0;
    if (mid >= L) 
        ans += judgesum(ls(id), L, R);
    if (mid + 1 <= R) 
        ans += judgesum(rs(id), L, R);
    return ans;
}

int judgemax(int id, int L, int R) {
    if (l[id] >= L && r[id] <= R) 
        return mx[id];
    pushdown(id);
    int mid = l[id] + r[id] >> 1;
    int ans = -ini;
    if (mid >= L) 
        ans = judgemax(ls(id), L, R);
    if (mid + 1 <= R) 
        ans = max(ans, judgemax(rs(id), L, R));
    return ans;
}
//计算右边界的下一个地址
string next(string s) {
    string result = s;
    bool carry = true;
    for (int i = s.size() - 1; i >= 0; i--) {
        if (s[i] == ':')
            continue;
        else if (s[i] == 'f' && carry)
            result[i] = '0';
        else if (s[i] == '9') {
            result[i] = 'a';
            carry = false;
            break;
        }
        else {
            result[i] = s[i] + 1;
            carry = false;
            break;
        }
    }
    return result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> n >> q;
	for (int i = 1; i <= q; i++) {
		cin >> act[i].op;
		if (act[i].op == 1) {
			cin >> act[i].id >> act[i].l >> act[i].r;
			saveadds.push_back(act[i].l);
			saveadds.push_back(act[i].r);
			saveadds.push_back(next(act[i].r));
		}
        else if (act[i].op == 2) {
            cin >> act[i].l;
            saveadds.push_back(act[i].l);
        }
        else {
            cin >> act[i].l >> act[i].r;
            saveadds.push_back(act[i].l);
            saveadds.push_back(act[i].r);
            saveadds.push_back(next(act[i].r));
        }
	}
    sort(saveadds.begin(), saveadds.end());
    //去除数组中的重复元素
    vector<string> unique_values;  // 用于存储去重后的唯一元素
    for (int i = 0; i < saveadds.size(); i++)
        if (i == 0 || saveadds[i] != saveadds[i - 1])
            unique_values.push_back(saveadds[i]);
    saveadds = unique_values;  // 将原容器替换为去重后的结果
    //建树
    build(1, 1, saveadds.size());
    for (int i = 1; i <= q; i++) {
        if (act[i].op == 1) {
            int ll = find(act[i].l), rr = find(act[i].r);
            //该地址全部未被分配
            if (judgemin(1, ll, rr) == ini) {   
                cout << "YES\n";
                update(1, ll, rr, act[i].id);
            }
            //该地址是否只分配给了一个人 
            else if (judgemin(1, ll, rr) == act[i].id && judgemax(1, ll, rr) == act[i].id) {
                //该地址本来就已经全部分配给了id 
                if (judgesum(1, ll, rr) == (rr - ll + 1))
                    cout << "NO\n";
                else {
                    cout << "YES\n";
                    update(1, ll, rr, act[i].id);
                }
            }
            //该地址分配给了其他人
            else
                cout << "NO\n";
        }
        else if (act[i].op == 2) {
            int ll = find(act[i].l);
            int t = judgemax(1, ll, ll);
            if (t != -ini)
                cout << t << "\n";
            else
                cout << "0\n";
        }
        else {
            int ll = find(act[i].l), rr = find(act[i].r);
            int id = judgemin(1, ll, rr);
            //该地址是否只分配给了一个人 
            if (id == judgemax(1, ll, rr) && judgesum(1, ll, rr) == (rr - ll + 1))
                cout << id << "\n";
            else
                cout << "0\n";
        }
    }
    return 0;
}
