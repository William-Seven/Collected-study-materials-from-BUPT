#include<iostream>
#include<vector>
#include<algorithm>
#include<string.h>
using namespace std;
int N, M, K;
int foodbit[101];				//位图表示
int waitmax[101][11];			//记录从酒店i出发配送食材j的最大等待时间
bool passneed[101];				//标记是否需要经过该酒店
int onetime;					//配送所有酒店的单程时间
int maxnn = 0, minnn = 0;		//记录二分时的左右边界
bool dp[11][1 << 10];			//表示是否可送达K种食材的配送组合
int flag[101];					//位图标记某酒店是否适合配送每一个食材
struct node {
	int v, w;
	node(int v, int w):v(v),w(w){}
};
vector<node> map[101];

int dfs(int u, int pre) {
	int ret = 0;
	//深度优先遍历u为顶点的所有路径
	for (const auto& x : map[u]) {
		int v = x.v;
		int w = x.w;
		if (v == pre)
			continue;
		int re = dfs(v, u);
		//处理必经点（不需要食材但子节点需要且必经过该节点）
		if (passneed[v]) {
			passneed[u] = true;
			onetime += w;
			ret = max(ret, re + w);
		}
	}
	return ret;
}

void initial() {
	for (int i = 1; i <= N; i++)
		for (int j = 0; j < K; j++) {
			//事先标记
			memset(passneed, 0, sizeof(passneed));
			for (int k = 1; k <= N; k++)
				if (foodbit[k] >> j & 1)
					passneed[k] = true;
			//初始化单程时间
			onetime = 0;
			//从第i个酒店开始的情况下，找到最长的路径
			int maxn = dfs(i, -1);
			//其他路径去并返回，最长路径只走一次不返回
			waitmax[i][j] = onetime * 2 - maxn;
			//为二分查找的边界做准备
			if (waitmax[i][j] > maxnn)
				maxnn = waitmax[i][j];
			else if (waitmax[i][j] < minnn)
				minnn = waitmax[i][j];
		}
}

bool judge(int mid) {
	memset(flag, 0, sizeof(flag));
	memset(dp, 0, sizeof(dp));
	//位图标记酒店i是否适合配送食材j
	for (int i = 1; i <= N; i++)
		for (int j = 0; j < K; j++)
			if (waitmax[i][j] <= mid)
				flag[i] |= 1 << j;

	dp[0][0] = true;
	//遍历酒店，以酒店i为出发点
	for (int i = 1; i <= N; i++) {
		//遍历检查点，酒店i在j个检查点时的配送情况
		for (int j = 1; j <= M; j++)
			for (int k = 0; k < (1 << K); k++)
				dp[j][k | flag[i]] |= dp[j - 1][k];
		if (dp[M][(1 << K) - 1])
			return true;
	}
	return dp[M][(1 << K) - 1];
}

void work() {
	if (M == K) {
		int ansmax = -1;
		for (int j = 0; j < K; j++) {
			int foodmin = maxnn;
			for (int i = 1; i <= N; i++)
				if (waitmax[i][j] < foodmin)
					foodmin = waitmax[i][j];
			ansmax = max(ansmax, foodmin);
		}
		cout << ansmax << "\n";
		return;
	}

	int l = minnn, r = maxnn, ans = 0;
	while (l <= r) {
		int mid = (l + r) / 2;
		if (judge(mid)) {
			r = mid - 1;
			ans = mid;
		}
		else
			l = mid + 1;
	}
	cout << ans << "\n";
	return;
}

int main()
{
	ios::sync_with_stdio(false);
	//输入
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++)
		for (int j = 0; j < K; j++) {
			int temp;
			cin >> temp;
			if (temp)
				foodbit[i] |= (1 << j);
		}
	for (int i = 1; i < N; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		map[u].emplace_back(v, w);
		map[v].emplace_back(u, w);
	}
	//预处理
	initial();
	//计算结果
	work();
	return 0;
}