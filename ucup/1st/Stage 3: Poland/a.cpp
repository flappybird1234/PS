#include <bits/stdc++.h>
using namespace std;
void solve() {
	int N;
	vector<pair<string, string>> pss;
	cin >> N;
	int i;
	string s, t;
	for (i = 1; i <= N; i++) {
		cin >> s >> t;
		pss.emplace_back(s, t);
	}
	auto chk = [&](int a, int b, int c) {
		map<string, int> mp;
		int i;
		for (auto& [s, t] : pss) {
			string ss, tt;
			for (i = 0; i < a; i++) if (i < s.size()) ss.push_back(s[i]);
			for (i = 0; i < b; i++) if (i < t.size()) tt.push_back(t[i]);
			mp[ss + tt]++;
		}
		int lim = 1;
		for (i = 0; i < c; i++) lim *= 10;
		for (auto& [_, cnt] : mp) {
			if (cnt > lim) return false;
		}
		return true;
	};
	int n, a, b, c;
	for (n = 1; n <= 8; n++) {
		for (a = 0; a <= n; a++) {
			for (b = 0; b <= n; b++) {
				c = n - a - b;
				if (c < 0) continue;
				if (chk(a, b, c)) {
					cout << a << ' ' << b << ' ' << c << '\n';
					return;
				}
			}
		}
	}
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int T;
	cin >> T;
	while (T--) solve();
}