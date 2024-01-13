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
//����
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
//���������г���s��λ��
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
//���½ڵ���Ϣ
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
//�жϸõ�ַ�Ƿ��Ѿ�ȫ�������id 
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
//�����ұ߽����һ����ַ
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
    //ȥ�������е��ظ�Ԫ��
    vector<string> unique_values;  // ���ڴ洢ȥ�غ��ΨһԪ��
    for (int i = 0; i < saveadds.size(); i++)
        if (i == 0 || saveadds[i] != saveadds[i - 1])
            unique_values.push_back(saveadds[i]);
    saveadds = unique_values;  // ��ԭ�����滻Ϊȥ�غ�Ľ��
    //����
    build(1, 1, saveadds.size());
    for (int i = 1; i <= q; i++) {
        if (act[i].op == 1) {
            int ll = find(act[i].l), rr = find(act[i].r);
            //�õ�ַȫ��δ������
            if (judgemin(1, ll, rr) == ini) {   
                cout << "YES\n";
                update(1, ll, rr, act[i].id);
            }
            //�õ�ַ�Ƿ�ֻ�������һ���� 
            else if (judgemin(1, ll, rr) == act[i].id && judgemax(1, ll, rr) == act[i].id) {
                //�õ�ַ�������Ѿ�ȫ���������id 
                if (judgesum(1, ll, rr) == (rr - ll + 1))
                    cout << "NO\n";
                else {
                    cout << "YES\n";
                    update(1, ll, rr, act[i].id);
                }
            }
            //�õ�ַ�������������
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
            //�õ�ַ�Ƿ�ֻ�������һ���� 
            if (id == judgemax(1, ll, rr) && judgesum(1, ll, rr) == (rr - ll + 1))
                cout << id << "\n";
            else
                cout << "0\n";
        }
    }
    return 0;
}
