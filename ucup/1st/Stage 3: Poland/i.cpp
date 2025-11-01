#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
#define MAX 6060
#define INF 1e9
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
namespace bit {
	int tree[MAX];
	int N;
	void init(int _N) {
		N = _N;
		int i;
		for (i = 0; i <= N + 10; i++) tree[i] = 0;
	}
	void upd(int i, int x) { while (i <= N) { tree[i] += x, i += i & -i; } }
	int get(int i) { int ans = 0; while (i) { ans += tree[i], i -= i & -i; } return ans; }
}
int A[MAX];
int dp[MAX][MAX];
int C[MAX][MAX];
void dnc(int k, int s, int e, int l, int r) {
	if (l > r) return;
	int m = l + r >> 1;
	int mv;
	int mn;
	mv = 0;
	mn = 2e9;
	int i;
	for (i = s; i <= e; i++) {
		if (i > m) continue;
		int val = dp[k - 1][i - 1] + C[i][m];
		if (mn > val) {
			mn = val;
			mv = i;
		}
	}
	dp[k][m] = mn;
	dnc(k, s, mv, l, m - 1);
	dnc(k, mv, e, m + 1, r);
}
void solve() {
	int N, K;
	cin >> N >> K;
	K++;
	int i, j;
	for (i = 0; i <= N + 10; i++) {
		for (j = 0; j <= N + 10; j++) {
			dp[i][j] = C[i][j] = 0;
		}
	}
	vector<int> v;
	for (i = 1; i <= N; i++) {
		cin >> A[i];
		v.push_back(A[i]);
	}
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	for (i = 1; i <= N; i++) A[i] = lower_bound(v.begin(), v.end(), A[i]) - v.begin() + 1;
	for (i = 1; i <= N; i++) {
		C[i][i] = 0;
		bit::init(N);
		int acnt = 0;
		bit::upd(A[i], 1);
		for (j = i + 1; j <= N; j++) {
			acnt++;
			C[i][j] = C[i][j - 1] + (acnt - bit::get(A[j]));
			bit::upd(A[j], 1);
		}
	}
	for (i = 1; i <= N; i++) dp[1][i] = C[1][i];
	for (i = 2; i <= K; i++) {
		dnc(i, 1, N, 1, N);
		for (j = 1; j <= N; j++) dp[i][j] = min(dp[i][j], dp[i - 1][j]);
	}
	cout << dp[K][N] << '\n';
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int T;
	cin >> T;
	while (T--) solve();
}