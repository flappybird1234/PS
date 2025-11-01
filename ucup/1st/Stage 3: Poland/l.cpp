#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
#define MAX 2020202
#define INF 1e9
#define B 50505
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int chk[MAX];

ll sum[MAX];
pii edges[MAX];
int C[MAX];
vector<int> adj[MAX];
multiset<int> ms[MAX];

void solve() {
	int N, P;
	cin >> N >> P;
	int i, x;

	for (i = 0; i <= N + 100; i++) {
		sum[i] = chk[i] = C[i] = 0;
		edges[i] = pii(0, 0);
		adj[i].clear();
		ms[i].clear();
	}

	for (i = 1; i <= P; i++) {
		cin >> x;
		chk[x] = 1;
	}
	int a, b;
	for (i = 1; i < N; i++) {
		cin >> a >> b >> C[i];
		edges[i] = pii(a, b);
		ms[a].emplace(C[i]);
		ms[b].emplace(C[i]);
		sum[a] += C[i];
		sum[b] += C[i];
	}
	int K;
	cin >> K;
	vector<int> rems;
	for (i = 1; i <= K; i++) {
		cin >> a;
		rems.push_back(a);
	}
	sort(rems.begin(), rems.end(), [&](int a, int b) {return C[a] > C[b]; });
	auto f = [&](int v) {
		if (chk[v]) return true;
		if (sum[v] & 1) return false;
		if (ms[v].size() == 1) return false;
		int b = *ms[v].rbegin();
		return b <= sum[v] / 2;
	};
	for (i = 1; i <= N; i++) if (!f(i)) {
		cout << "NIE\n";
		return;
	}
	for (auto e : rems) {
		auto& [a, b] = edges[e];
		for (auto x : { a, b }) {
			ms[x].erase(ms[x].find(C[e]));
			sum[x] -= C[e];
			if (!f(x)) {
				cout << "NIE\n";
				return;
			}
		}
	}
	cout << "TAK\n";
	for (auto e : rems) cout << e << ' ';
	cout << '\n';
}

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int T;
	cin >> T;
	while (T--) solve();
}