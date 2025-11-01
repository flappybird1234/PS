#include <bits/stdc++.h>
#define MAX 1010101
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
ll ccw(pii p1, pii p2, pii p3) {
	return 1ll * p1.first * p2.second + 1ll * p2.first * p3.second + 1ll * p3.first * p1.second - (1ll * p2.first * p1.second + 1ll * p3.first * p2.second + 1ll * p1.first * p3.second);
}
int P[MAX];
void solve() {
	int N;
	cin >> N;
	int i;
	for (i = 1; i <= N; i++) cin >> P[i];
	vector<int> stk;
	for (i = 1; i <= N; i++) {
		while (stk.size() > 1) {
			int p2, p1;
			p1 = stk.back();
			stk.pop_back();
			p2 = stk.back();
			if (ccw(pii(p2, P[p2]), pii(p1, P[p1]), pii(i, P[i])) < 0) {
				stk.push_back(p1);
				break;
			}
		}
		stk.push_back(i);
	}
	ll ans = 0;
	for (i = 1; i < stk.size(); i++) ans += ((ll)P[stk[i]] + (ll)P[stk[i - 1]]) * ((ll)stk[i] - stk[i - 1]);
	cout << ans << '\n';
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int T;
	cin >> T;
	while (T--) solve();
}