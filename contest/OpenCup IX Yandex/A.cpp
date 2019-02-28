#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 500000 + 7;

const ll BASE = 880301;
const ll MOD = 1000000000 + 7;
const ll MEOW = 65537;

int n;
ll ans;
int sz[MAX_N];
int mx[MAX_N];
ll fact[MAX_N];
ll dd[MAX_N];
vector<int> G[MAX_N];

int dfs(int u, int fa = 0) {
	sz[u] = 1;
	for (int v : G[u]) {
		if (v == fa)
			continue;
		int t = dfs(v, u);
		mx[u] = max(mx[u], t);
		sz[u] += t;
	}
	mx[u] = max(mx[u], n - sz[u]);
	return sz[u];
}

ll dfs2(int u, int fa, int dep = 0) {
	vector<ll> vs;
	for (int v : G[u]) {
		if (v != fa) {
			vs.push_back(dfs2(v, u, dep + 1));
		}
	}
	sort(vs.begin(), vs.end());
	ll hv = 0;
	for (ll x : vs) 
		hv = (hv * BASE + x) % MOD;
	hv ^= dd[dep];
	for (int i = 0, j = 0; i < (int)vs.size(); i = j) {
		while (j < (int)vs.size() && vs[j] == vs[i])
			j++;
		ans = ans * fact[j - i] % MOD;
	}
	return hv;
}

int main() {
	dd[0] = MEOW;
	for (int i = 1; i < MAX_N; i++)
		dd[i] = dd[i - 1] * MEOW % MOD;

	fact[0] = 1;
	for (int i = 1; i < MAX_N; i++)
		fact[i] = fact[i - 1] * i % MOD;

	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1);
	vector<int> centroid = {1};
	for (int i = 2; i <= n; i++) {
		if (mx[i] < mx[centroid[0]])
			centroid = {i};
		else if (mx[i] == mx[centroid[0]])
			centroid.push_back(i);
	}
	ans = 1;
	if (centroid.size() == 1) 
		dfs2(centroid[0], 0);
	else {
		ll hv1 = dfs2(centroid[0], centroid[1]);
		ll hv2 = dfs2(centroid[1], centroid[0]);
		if (hv1 == hv2)
			ans = ans * 2 % MOD;
	}
	printf("%lld\n", ans);
	return 0;
}
