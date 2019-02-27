#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 200000 + 7;

struct Bit {
    int n;
    int tr[MAX_N << 1];
    
    void init(int _n) {
        n = _n;
        memset(tr, 0, sizeof(tr));
    }

    void add(int p, int x) {
        for (int i = p; i <= n; i += i & -i)
            tr[i] += x;
    }

    int query(int p) {
        int res = 0;
        for (int i = p; i > 0; i -= i & -i)
            res += tr[i];
        return res;
    }
} bit;

int dp[MAX_N];

vector<int> G[MAX_N];
vector<tuple<int, int, int  > > es[MAX_N];

int dep[MAX_N], anc[MAX_N][20];
int dfs_clock, dfn_st[MAX_N], dfn_ed[MAX_N];

void dfs(int u, int fa) {
    dfn_st[u] = ++dfs_clock;
    dep[u] = dep[fa] + 1;
    anc[u][0] = fa;
    for (int i = 1; i < 20; i++)
        anc[u][i] = anc[anc[u][i - 1]][i - 1];
    for (int v : G[u])
        dfs(v, u);
    dfn_ed[u] = ++dfs_clock;
}

void dfs2(int u) {
    int sum = 0;
    for (int v : G[u]) {
        dfs2(v);
        sum += dp[v];
    }
    dp[u] = sum;
    for (tuple<int, int, int> e : es[u]) {
        int tmp = bit.query(dfn_st[get<0>(e)]) + bit.query(dfn_st[get<1>(e)]) + get<2>(e) + sum;
        dp[u] = max(dp[u], tmp);
    }
    bit.add(dfn_st[u], sum - dp[u]);
    bit.add(dfn_ed[u] + 1, dp[u] - sum);
}

int get_lca(int u, int v) {
    if (dep[u] < dep[v])
        swap(u, v);
    for (int i = 0; i < 20; i++) {
        if ((dep[u] - dep[v]) & (1 << i))
            u = anc[u][i];
    }
    for (int i = 19; i >= 0; i--) {
        if (anc[u][i] != anc[v][i]) {
            u = anc[u][i];
            v = anc[v][i];
        }
    }
    if (u != v) {
        u = anc[u][0];
        v = anc[v][0];
    }
    return u;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 2; i <= n; i++) {
        int p;
        scanf("%d", &p);
        G[p].push_back(i);
    }
    dfs(1, 0);
    bit.init(dfs_clock + 1);
    while (m--) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        int lca = get_lca(u, v);
        es[lca].emplace_back(u, v, c);
    }
    dfs2(1);
    printf("%d\n", dp[1]);
    return 0;
}
