#include <bits/stdc++.h>
#define MAX 1010101
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
int ban[MAX];
vector<pii> adj[MAX];
#define INF 1e9
int dist[MAX];
int vis[MAX];
int ans[MAX];
void solve() {
	int N, K;
	cin >> N >> K;
	int i, a, b;

	for (i = 0; i <= max(N, K) + 10; i++) {
		ban[i] = dist[i] = vis[i] = ans[i] = 0;
		adj[i].clear();
	}

	for (i = 1; i <= K; i++) {
		cin >> a >> b;
		adj[a].emplace_back(b, i);
	}
	int S;
	cin >> S;
	while (S--) {
		cin >> a;
		ban[a] = 1;
	}
	priority_queue<pii> pq;
	for (i = 1; i <= N; i++) {
		if (ban[i]) dist[i] = -INF;
		else {
			dist[i] = INF;
			pq.emplace(dist[i], i);
		}
	}
	while (pq.size()) {
		auto t = pq.top().second;
		pq.pop();
		if (vis[t]) continue;
		vis[t] = 1;
		for (auto& [v, c] : adj[t]) {
			if (!ban[v]) continue;
			if (c < dist[t] && c > dist[v]) {
				dist[v] = c;
				pq.emplace(dist[v], v);
			}
		}
	}
	for (i = 1; i <= N; i++) {
		if (ban[i] && dist[i] < 0) {
			cout << "NIE" << '\n';
			return;
		}
		if (ban[i]) ans[dist[i]] = 1;
	}
	cout << "TAK\n";
	for (i = 1; i <= K; i++) cout << "NT"[ans[i]];
	cout << '\n';
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int T;
	cin >> T;
	while (T--) solve();
}