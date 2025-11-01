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
typedef long double ld;

int N, K;

vector<int> v[MAX];
vector<pii> ops;
void op(int a, int b) {
	ops.emplace_back(a, b);
	v[b].push_back(v[a].back());
	v[a].pop_back();
	assert(ops.size() <= 1'000'000);
	assert(v[b].size() <= K);
}

void lflip(int x) {
	assert(x > 0);
	int i;
	for (i = 0; i < K; i++) op(x, x - 1);
}
void rflip(int x) {
	assert(x <= N);
	int i;
	for (i = 0; i < K; i++) op(x, x + 1);
}

void sortv(int x) {
	assert(v[x - 1].empty());
	assert(v[x + 1].empty());
	lflip(x);
	while (v[x - 1].size()) {
		int mn = *minmax_element(v[x - 1].begin(), v[x - 1].end()).first;
		while (v[x - 1].size()) {
			int b = v[x - 1].back();
			op(x - 1, x);
			if (b != mn) op(x, x + 1);
		}
		while (v[x + 1].size()) {
			op(x + 1, x);
			op(x, x - 1);
		}
	}
}

/*
*
xyzw

.b..
dac.
y->z->w
....
dacb
x->y->z->w
...d
.acb
y->x
...d
a.cb
z->y
...d
ac.b
w->z
....
acdb
w->z->y->x
b...
acd.
z->w
b...
ac.d
y->z->w
b..c
a..d
x->y->z
...c
a.bd
x->y
...c
.abd
z->y
.b.c
.a.d
w->z
.b..
.acd
w->z
.bd.
.ac.
*/
void f(int x, int y, int z, int w) {
	op(y, z);
	op(z, w);
	op(x, y);
	op(y, z);
	op(z, w);
	op(y, x);
	op(z, y);
	op(w, z);
	op(w, z);
	op(z, y);
	op(y, x);
	op(z, w);
	op(y, z);
	op(z, w);
	op(x, y);
	op(y, z);
	op(x, y);
	op(z, y);
	op(w, z);
	op(w, z);
}

void merge(int a, int b) {
	assert(b == a + 1);
	assert(v[a - 1].empty());
	assert(v[b + 1].empty());
	lflip(a); //K
	rflip(b); //K
	int loc = a;
	int chk = 0;
	while (v[a - 1].size() || v[b + 1].size()) { //4K
		bool c = 0;
		if (v[a - 1].empty()) c = 1;
		else if (v[b + 1].size() && v[a - 1].back() > v[b + 1].back()) c = 1;

		if (c) {
			op(b + 1, b);
			if (loc == a) op(b, a);
		}
		else {
			if (v[a - 1].size() == 1 && v[b + 1].empty()) {
				chk = 1;
				break;
			}
			op(a - 1, a);
			if (loc == b) op(a, b);
		}
		loc ^= a ^ b;
	}
	if (chk) f(a - 1, a, b, b + 1); //20

	rflip(b); //K
	rflip(a); //K

	assert(v[b].size() == v[b + 1].size());
	while (v[b].size()) { //4K
		op(b, a); //K
		if (v[a - 1].size() < K) op(a, a - 1);
		op(b + 1, b); //K
		op(b, a); //K
		if (v[a - 1].size() < K) op(a, a - 1);
	}

	while (v[a].size()) { //2K
		op(a, b);
		op(b, b + 1);
	}
	while (v[a - 1].size()) { //2K
		op(a - 1, a);
		op(a, b);
	}
	lflip(b); //K
	lflip(b + 1); //K
}

bool eq(vector<int>& v) {
	for (int i = 1; i < v.size(); i++) if (v[i] != v[i - 1]) return false;
	return true;
}

void solve() {
	cin >> N >> K;
	int i, j;
	ops.clear();
	for (i = 0; i <= N + 1; i++) v[i].clear();
	for (i = 1; i <= N; i++) {
		int a;
		for (j = 1; j <= K; j++) {
			cin >> a;
			v[i].push_back(a);
		}
	}

	if (K == 1) {
		cout << "TAK\n0\n";
		return;
	}

	for (i = N; i >= 2; i--) rflip(i);
	for (i = 1; i <= N; i++) {
		sortv(i);
		lflip(i);
		if (i < N) lflip(i + 2);
	}
	for (i = N - 1; i >= 0; i--) rflip(i);

	int T = N;
	while (T--) {
		for (i = N; i >= 3; i--) rflip(i);
		for (i = 2; i <= N; i++) {
			merge(i - 1, i);
			if (i < N) {
				lflip(i - 1);
				lflip(i + 2);
			}
		}
		for (i = N - 3; i >= 0; i--) rflip(i);
	}

	for (i = N; i >= 1; i--) rflip(i);
	for (i = 2; i <= N + 1; i++) {
		while (v[i].size()) {
			op(i, i - 1);
			op(i - 1, i - 2);
		}
	}
	int p = N - 1;
	for (i = N + 1; i >= 0; i--) {
		if (p < 0) break;
		if (i == p) {
			if (!eq(v[i])) {
				cout << "NIE\n";
				return;
			}
		}
		while (v[i].size() < K && p >= 0) {
			if (p >= 0 && v[p].empty()) p--;
			if (p < 0) break;
			if (i == p) {
				if (eq(v[i])) {
					p--;
					continue;
				}
				else {
					cout << "NIE\n";
					return;
				}
			}
			if (v[i].size() && v[i].back() != v[p].back()) break;
			int j;
			for (j = p; j < i; j++) op(j, j + 1);
		}
	}
	for (i = 0; i <= N + 1; i++) eq(v[i]);
	cout << "TAK\n";
	cout << ops.size() << '\n';
	for (auto& [a, b] : ops) cout << a << ' ' << b << '\n';
}

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int T;
	cin >> T;
	while (T--) solve();
}