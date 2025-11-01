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

ll P[MAX];
ll V[MAX];
void solve() {
	int N;
	ld v;
	cin >> N >> v;
	int i;
	for (i = 1; i <= N; i++) cin >> P[i] >> V[i];
	ld l, r;
	l = 0;
	r = 1e15;
	int T = 100;
	while (T--) {
		ld m = (l + r) / 2;
		ld mv1, mv2;
		mv1 = mv2 = 1e18;
		for (i = 1; i <= N; i++) {
			if (P[i] > 0) mv1 = min(mv1, P[i] - m * V[i]);
			else mv2 = min(mv2, -P[i] - m * V[i]);
		}
		if (mv1 + mv2 <= 0) r = m;
		else l = m;
	}
	cout << l * v << '\n';
}

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cout << fixed;
	cout.precision(19);
	int T;
	cin >> T;
	while (T--) solve();
}