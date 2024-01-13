#include<bits/stdc++.h>
#define mod 998244353
using namespace std;
const int N = 1 << 21;
int n, dp[25][N], fac[N];
int main()
{
	ios::sync_with_stdio(false);
	cin >> n;
	fac[0] = 1;
	for (int i = 1; i <= (1 << n); i++)
		fac[i] = 1ll * fac[i - 1] * i% mod;
	dp[0][0] = 1;
	for(int i = 0; i <= n; i++)
		for (int j = (1 << n) - (1 << n - i); j >= 0; j--) {
			if (i < n)
				dp[i + 1][j + (1 << n - i - 1) - 1] += 1ll * dp[i][j] % mod * (1 << n - i - 1) % mod;
			if (j)
				dp[i][j - 1] += 1ll * dp[i][j] % mod * j % mod;
		}
	int times = 1 << n;
	for (int k = 1; k <= 1 << n; k++)
		cout << 1ll * dp[n][(1 << n) - k] * fac[(1 << n) - k] % mod * times % mod << "\n";
	return 0;
}
