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
int mp[30][30];
int N, K;
void solve() {
	cin >> N >> K;
	int i, j;
	string s;
	memset(mp, 0, sizeof(mp));
	for (i = 1; i <= N; i++) {
		cin >> s;
		for (j = 1; j <= N; j++) {
			if (s[j - 1] == 'o') mp[i][j] = 1;
			if (s[j - 1] == 'x') mp[i][j] = 2;
		}
	}
	int cnt[2] = { 0, 0 };
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) {
			if (mp[i][j]) cnt[mp[i][j] - 1]++;
		}
	}
	if (abs(cnt[0] - cnt[1]) > 1) {
		cout << "NIE\n";
		return;
	}
	int rem = 0;
	if (cnt[0] != cnt[1]) rem = 1 + (cnt[0] < cnt[1]);
	auto chk2 = [&]() {
		int i, j, k, d;
		for (d = 1; d <= 3; d++) {
			for (i = 1; i <= N; i++) {
				for (j = 1; j <= N; j++) {
					if (!mp[i][j]) continue;
					int bum = 0;
					for (k = 1; k < K; k++) bum |= mp[i + k * (d & 1)][j + k * (d >> 1)] != mp[i][j];
					if (!bum) return true;
				}
			}
		}
		return false;
	};
	auto chk = [&]() {
		int i;
		if (chk2()) return true;
		for (i = 1; i <= N; i++) reverse(mp[i] + 1, mp[i] + N + 1);
		auto res = chk2();
		for (i = 1; i <= N; i++) reverse(mp[i] + 1, mp[i] + N + 1);
		return res;
	};
	if (!chk() && cnt[0] + cnt[1] != N * N) {
		cout << "NIE\n";
		return;
	}
	pii last;
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) {
			if (mp[i][j]) {
				if (rem && rem != mp[i][j]) continue;
				int v = mp[i][j];
				mp[i][j] = 0;
				if (!chk()) {
					last = pii(i, j);
					mp[i][j] = v;
					goto end;
				}
				mp[i][j] = v;
			}
		}
	}
end:
	if (!last.first) {
		cout << "NIE\n";
		return;
	}
	vector<pii> v1, v2;
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) {
			if (!mp[i][j]) continue;
			if (pii(i, j) == last) continue;
			if (mp[i][j] == 1) v1.emplace_back(i, j);
			else v2.emplace_back(i, j);
		}
	}
	vector<pii> ansv;
	if (mp[last.first][last.second] == 1) swap(v1, v2);
	ansv.push_back(last);
	while (v1.size() || v2.size()) {
		if (v1.size()) {
			ansv.push_back(v1.back());
			v1.pop_back();
		}
		if (v2.size()) {
			ansv.push_back(v2.back());
			v2.pop_back();
		}
	}
	cout << "TAK\n";
	reverse(ansv.begin(), ansv.end());
	for (auto& [a, b] : ansv) cout << a << ' ' << b << '\n';
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int T;
	cin >> T;
	while (T--) solve();
}