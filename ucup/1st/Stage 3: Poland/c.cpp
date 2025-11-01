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
void solve() {
	string s;
	cin >> s;
	int i;
	int cnt = 0;
	for (i = 3; i < s.size(); i++) {
		if (s[i - 3] != 'a') continue;
		if (s[i - 2] != 'n') continue;
		if (s[i - 1] != 'i') continue;
		if (s[i - 0] != 'a') continue;
		s[i] = 'z';
		cnt++;
	}
	cout << cnt << '\n';
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int T;
	cin >> T;
	while (T--) solve();
}