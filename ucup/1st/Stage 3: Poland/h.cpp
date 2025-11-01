#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
#define MAX 303030
#define INF 1e9
#define B 50505
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
vector<int> adj[MAX], dag[MAX];
pii edges[MAX];
int C[MAX];
int dist[MAX];
int vis[MAX];
int get_next(int x, int e) {
	return edges[e].first ^ edges[e].second ^ x;
}

// PST
namespace PST {
	struct node {
		int l, r;
		int cnt;
		node(int c = 0) {
			l = r = 0;
			cnt = c;
		}
	};

	vector<node> MEM;

	void init() {
		MEM.clear();
		MEM.push_back(node());
		MEM.push_back(node());
	}

	int make_node(int x = 0) { //copy x
		int res = MEM.size();
		MEM.push_back(node(MEM[x]));
		return res;
	}

	int getl(int n) { return MEM[n].l; }
	int getr(int n) { return MEM[n].r; }

	int upd(int s, int e, int i, int n) {
		if (e < i || i < s) return n;
		int cur = make_node(n);
		if (s == e) {
			MEM[cur].cnt++;
			return cur;
		}
		int m = s + e >> 1;
		MEM[cur].l = upd(s, m, i, MEM[n].l);
		MEM[cur].r = upd(m + 1, e, i, MEM[n].r);
		MEM[cur].cnt = MEM[getl(cur)].cnt + MEM[getr(cur)].cnt;
		return cur;
	}

	pii lb(int s, int e, int k, int n) {
		if (k < s) return pii(0, 0);
		if (!MEM[n].cnt) return pii(0, 0);
		if (s == e) return pii(s, MEM[n].cnt);
		int m = s + e >> 1;
		pii res = lb(m + 1, e, k, getr(n));
		if (res.second) return res;
		return lb(s, m, k, getl(n));
	}
}

int rt[MAX];
int nxt[MAX];
int chk[MAX];

void solve() {
	int N, M;
	cin >> N >> M;
	int i;

	PST::init();
	for (i = 0; i <= max(N, M) + 10; i++) {
		adj[i].clear();
		dag[i].clear();
		edges[i].first = edges[i].second = C[i] = dist[i] = vis[i] = rt[i] = nxt[i] = chk[i] = 0;
	}

	int a, b;
	for (i = 1; i <= M; i++) {
		cin >> a >> b >> C[i];
		edges[i] = pii(a, b);
		adj[a].push_back(i);
		adj[b].push_back(i);
	}
	for (i = 2; i <= N; i++) dist[i] = 1e9;
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	pq.emplace(0, 1);
	while (pq.size()) {
		int t = pq.top().second;
		pq.pop();
		if (vis[t]) continue;
		vis[t] = 1;
		for (auto& e : adj[t]) {
			int v = get_next(t, e);
			if (dist[v] > dist[t] + C[e]) {
				dist[v] = dist[t] + C[e];
				pq.emplace(dist[v], v);
			}
		}
	}
	for (i = 1; i <= M; i++) {
		auto& [a, b] = edges[i];
		if (dist[a] > dist[b]) swap(a, b);
		if (dist[b] - dist[a] == C[i]) dag[a].push_back(i);
	}
	vector<int> v;
	for (i = 1; i <= N; i++) v.push_back(i);
	sort(v.begin(), v.end(), [&](int a, int b) { return dist[a] > dist[b]; });
	auto cmp = [&](int v1, int add1, int v2, int add2) {
		int lim = B;
		while (1) {
			pii r1 = PST::lb(1, B, lim, rt[v1]);
			pii r2 = PST::lb(1, B, lim, rt[v2]);
			if (add1 <= lim) {
				if (r1.first < add1) r1 = pii(add1, 1);
				else if (r1.first == add1) r1.second++;
			}
			if (add2 <= lim) {
				if (r2.first < add2) r2 = pii(add2, 1);
				else if (r2.first == add2) r2.second++;
			}
			if (r1 != r2) return r1 < r2;
			lim = r1.first - 1;
			if (lim <= 0) break;
		}
		return true; //¶È°°´Ù
	};
	for (auto x : v) {
		if (x == N) {
			rt[x] = chk[x] = 1;
			continue;
		}
		int pc = 0;
		for (auto e : dag[x]) {
			int v = get_next(x, e);
			if (!chk[v]) continue;
			if (!nxt[x] || cmp(nxt[x], pc, v, C[e])) {
				nxt[x] = v;
				pc = C[e];
			}
		}
		if (pc) {
			chk[x] = 1; 
			rt[x] = PST::upd(1, B, pc, rt[nxt[x]]);
		}
	}
	vector<int> ansv;
	for (i = 1; i != N; i = nxt[i]) ansv.push_back(i);
	ansv.push_back(N);
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