#include<iostream>
#include<vector>
#include<algorithm>
#include<string.h>
using namespace std;
int N, M, K;
int foodbit[101];				//λͼ��ʾ
int waitmax[101][11];			//��¼�ӾƵ�i��������ʳ��j�����ȴ�ʱ��
bool passneed[101];				//����Ƿ���Ҫ�����þƵ�
int onetime;					//�������оƵ�ĵ���ʱ��
int maxnn = 0, minnn = 0;		//��¼����ʱ�����ұ߽�
bool dp[11][1 << 10];			//��ʾ�Ƿ���ʹ�K��ʳ�ĵ��������
int flag[101];					//λͼ���ĳ�Ƶ��Ƿ��ʺ�����ÿһ��ʳ��
struct node {
	int v, w;
	node(int v, int w):v(v),w(w){}
};
vector<node> map[101];

int dfs(int u, int pre) {
	int ret = 0;
	//������ȱ���uΪ���������·��
	for (const auto& x : map[u]) {
		int v = x.v;
		int w = x.w;
		if (v == pre)
			continue;
		int re = dfs(v, u);
		//����ؾ��㣨����Ҫʳ�ĵ��ӽڵ���Ҫ�ұؾ����ýڵ㣩
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
			//���ȱ��
			memset(passneed, 0, sizeof(passneed));
			for (int k = 1; k <= N; k++)
				if (foodbit[k] >> j & 1)
					passneed[k] = true;
			//��ʼ������ʱ��
			onetime = 0;
			//�ӵ�i���Ƶ꿪ʼ������£��ҵ����·��
			int maxn = dfs(i, -1);
			//����·��ȥ�����أ��·��ֻ��һ�β�����
			waitmax[i][j] = onetime * 2 - maxn;
			//Ϊ���ֲ��ҵı߽���׼��
			if (waitmax[i][j] > maxnn)
				maxnn = waitmax[i][j];
			else if (waitmax[i][j] < minnn)
				minnn = waitmax[i][j];
		}
}

bool judge(int mid) {
	memset(flag, 0, sizeof(flag));
	memset(dp, 0, sizeof(dp));
	//λͼ��ǾƵ�i�Ƿ��ʺ�����ʳ��j
	for (int i = 1; i <= N; i++)
		for (int j = 0; j < K; j++)
			if (waitmax[i][j] <= mid)
				flag[i] |= 1 << j;

	dp[0][0] = true;
	//�����Ƶ꣬�ԾƵ�iΪ������
	for (int i = 1; i <= N; i++) {
		//�������㣬�Ƶ�i��j������ʱ���������
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
	//����
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
	//Ԥ����
	initial();
	//������
	work();
	return 0;
}