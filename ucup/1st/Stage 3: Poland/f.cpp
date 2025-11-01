#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
#define MAX 2010101
#define INF 1e9
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;

vector<int> adj[MAX];

int A[MAX], B[MAX], C[MAX], D[MAX];

int ncnt;

pii range[MAX];
int upv[MAX];
int downv[MAX];

int low[MAX], ord[MAX], vis[MAX], col[MAX];
vector<vector<int>> scc;
int cnt;
vector<int> stk;
void dfs(int x) {
	low[x] = ord[x] = ++cnt;
	vis[x] = 1;
	stk.push_back(x);
	for (auto v : adj[x]) {
		if (!ord[v]) {
			dfs(v);
			low[x] = min(low[x], low[v]);
		}
		else if (vis[v]) low[x] = min(low[x], ord[v]);
	}
	if (low[x] == ord[x]) {
		int t;
		vector<int> v;
		while (stk.size()) {
			t = stk.back();
			stk.pop_back();
			v.push_back(t);
			col[t] = scc.size();
			vis[t] = 0;
			if (t == x) break;
		}
		scc.push_back(v);
	}
}

pii make_node(int s, int e, int loc = 1) {
	range[loc] = pii(s, e);
	if (s == e) {
		upv[loc] = downv[loc] = s;
		return pii(s, s);
	}
	int m = s + e >> 1;
	int u, d;
	u = ++ncnt;
	d = ++ncnt;
	pii resl = make_node(s, m, loc * 2);
	pii resr = make_node(m + 1, e, loc * 2 + 1);
	adj[resl.first].push_back(u);
	adj[resr.first].push_back(u);
	adj[d].emplace_back(resl.second);
	adj[d].emplace_back(resr.second);
	upv[loc] = u;
	downv[loc] = d;
	return pii(u, d);
}

void make_edge(int s, int e, int l, int r, int v, int t, int loc = 1) {
	if (e < l || r < s) return;
	if (l <= s && e <= r) {
		if (t == 0) adj[upv[loc]].push_back(v);
		else adj[v].push_back(downv[loc]);
		return;
	}
	int m = s + e >> 1;
	make_edge(s, m, l, r, v, t, loc * 2);
	make_edge(m + 1, e, l, r, v, t, loc * 2 + 1);
}

vector<int> sadj[MAX], sradj[MAX];
int num[MAX];
int vord[MAX];

int deg[MAX];

int chk[MAX]; //위상정렬 한번 보면서 씀
int ans[MAX];

void dfs1(int x) {
	vis[x] = 1;
	for (auto v : sadj[x]) {
		if (vis[v]) continue;
		dfs1(v);
	}
}
void dfs2(int x) {
	vis[x] = 1;
	for (auto v : sradj[x]) {
		if (vis[v]) continue;
		dfs2(v);
	}
}

void solve() {
	int N, Q;
	cin >> N >> Q;
	int i;
	int MX = N * 3 + Q + N * 24 + 100;
	scc.clear();
	stk.clear();
	ncnt = cnt = 0;
	for (i = 0; i <= MX; i++) {
		adj[i].clear();
		sadj[i].clear();
		sradj[i].clear();
		A[i] = B[i] = C[i] = D[i] = range[i].first = range[i].second = upv[i] = downv[i] = low[i] = ord[i] = vis[i] = col[i] = num[i] = vord[i] = deg[i] = chk[i] = ans[i] = 0;
	}
	ncnt = N * 3 + Q;
	assert(ncnt < MX);
	make_node(1, N * 3);
	for (i = 1; i <= Q; i++) {
		cin >> A[i] >> B[i] >> C[i] >> D[i];
		make_edge(1, N * 3, A[i], B[i], N * 3 + i, 0);
		make_edge(1, N * 3, C[i], D[i], N * 3 + i, 1);
	}
	for (i = 1; i <= ncnt; i++) if (!ord[i]) dfs(i);
	int S = scc.size();
	for (i = 1; i <= ncnt; i++) {
		for (auto v : adj[i]) {
			if (col[i] != col[v]) {
				sadj[col[i]].push_back(col[v]);
				sradj[col[v]].push_back(col[i]);
			}
		}
	}
	vector<int> big;
	int mx = 0;
	queue<int> q;
	for (i = 0; i < S; i++) {
		for (auto v : scc[i]) {
			if (v <= N * 3) num[i]++;
		}
		mx = max(mx, num[i]);
		if (num[i] > N) big.push_back(i);

		deg[i] = sadj[i].size();
		if (!deg[i]) q.push(i);
	}
	int ocnt = 0;
	while (q.size()) {
		int t = q.front();
		q.pop();
		vord[ocnt++] = t;
		for (auto v : sradj[t]) {
			deg[v]--;
			if (!deg[v]) q.push(v);
		}
	}
	assert(ocnt == S);
	int psum = 0;
	int end = 0;
	for (i = 0; i < S; i++) {
		psum += num[vord[i]];
		chk[vord[i]] = 1;
		if (N <= psum && psum <= N * 2) {
			end = 1;
			break;
		}
	}
	if (end) {
		cout << "TAK\n";
		for (i = 1; i <= N * 3; i++) cout << "RF"[chk[col[i]]];
		cout << '\n';
		return;
	}
	assert(big.size() == 1); //큰게 2개였으면 하나 골랐을 시점에 끝났어야함

	for (i = 0; i < S; i++) vis[i] = 0;
	dfs1(big[0]);
	psum = 0;
	for (i = 0; i < S; i++) if (vis[i]) psum += num[i]; //방문한거는 1, 사용(F)
	if (N <= psum && psum <= N * 2) {
		cout << "TAK\n";
		for (i = 1; i <= N * 3; i++) cout << "RF"[vis[col[i]]];
		cout << '\n';
		return;
	}

	for (i = 0; i < S; i++) vis[i] = 0;
	dfs2(big[0]);
	psum = 0;
	for (i = 0; i < S; i++) if (!vis[i]) psum += num[i]; //방문한거는 사용하지 않음
	if (N <= psum && psum <= N * 2) {
		cout << "TAK\n";
		for (i = 1; i <= N * 3; i++) cout << "RF"[!vis[col[i]]];
		cout << '\n';
		return;
	}
	cout << "NIE\n";
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int T;
	cin >> T;
	while (T--) solve();
}