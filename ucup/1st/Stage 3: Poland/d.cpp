#include <bits/stdc++.h>
#define MAX 1010101
using namespace std;
int cnt;
vector<int> adj[MAX];
typedef pair<int, int> pii;
pii range[MAX];
int num[MAX];
vector<int> numv[MAX];
void dfs(int x, int p = 0) {
	num[x] = 1;
	if (p && adj[x].size() == 1) {
		cnt++;
		range[x] = { cnt, cnt };
		return;
	}
	range[x] = { 1e9, -1e9 };
	for (auto v : adj[x]) {
		if (v == p) continue;
		dfs(v, x);
		num[x] += num[v];
		range[x].first = min(range[x].first, range[v].first);
		range[x].second = max(range[x].second, range[v].second);
	}
	numv[num[x]].push_back(x);
}
void solve() {
	int N;
	cin >> N;

	int i;
	cnt = 0;
	for (i = 0; i <= N + 2; i++) adj[i].clear(), numv[i].clear(), range[i] = { 0, 0 }, num[i] = 0;

	int a, b;
	for (i = 1; i < N; i++) {
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	dfs(1);
	vector<int> ansv = { 1 };
	for (i = 2; i <= N; i++) {
		vector<pii> vpi;
		for (auto v : numv[i]) vpi.push_back(range[v]);
		sort(vpi.begin(), vpi.end());
		int pv = 0;
		int chk = 1;
		for (auto& [a, b] : vpi) {
			if (pv + 1 < a) {
				chk = 0;
				break;
			}
			pv = max(pv, b);
		}
		if (chk && pv == cnt) ansv.push_back(i);
	}
	cout << ansv.size() << '\n';
	for (auto v : ansv) cout << v << ' ';
	cout << '\n';
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int T;
	cin >> T;
	while (T--) solve();
}