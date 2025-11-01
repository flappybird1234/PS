#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
#define MAX 1000010
#define INF 1e9
#define B 50505
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int AT;
int arr[2][MAX];

ll get(ll n, int m) {
	if (n <= 0) return 0;
	if (AT && n < MAX && arr[m][n]) return arr[m][n];
	int i;
	ll d = 1;
	ll ans = 0;
	while (d <= n) {
		ll val = n / d;
		ll l, r;
		l = n / (val + 1) + 1;
		r = n / val;
		assert(l <= r && l == d);
		if (m == 0) ans += val * (r - l + 1);
		else ans += get(val - 1, 0) * (r - l + 1);
		d = r + 1;
	}
	if (AT && n < MAX) arr[m][n] = ans;
	return ans;
}


void solve() {
	ll N;
	cin >> N;
	cout << get(N, 1) << '\n';
}

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int T;
	cin >> T;
	if (T <= 30) AT = 1;
	while (T--) solve();
}