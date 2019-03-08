#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAX_N = 100000 + 7;

int mx[MAX_N << 2], add_tag[MAX_N << 2];

void add(int o, int x) {
    mx[o] += x;
    add_tag[o] += x;
}

void push(int o) {
    if (add_tag[o]) {
        add(o << 1, add_tag[o]);
        add(o << 1 | 1, add_tag[o]);
        add_tag[o] = 0;
    }
}

void pull(int o) {
    mx[o] = max(mx[o << 1], mx[o << 1 | 1]);
}

void modify(int o, int l, int r, int ql, int qr, int v) {
    if (ql <= l && r <= qr) {
        add(o, v);
        return;
    }
    int m = (l + r) >> 1;
    push(o);
    if (ql <= m)
        modify(o << 1, l, m, ql, qr, v);
    if (m < qr)
        modify(o << 1 | 1, m + 1, r, ql, qr, v);
    pull(o);
}

int par[MAX_N];
int mapping[MAX_N];
int dfs_clock;
bool vis[MAX_N];
vector<int> G[MAX_N];
int lb[MAX_N], rb[MAX_N];

void dfs(int u, int fa) {
    lb[u] = INF;
    int ch = 0;
    par[u] = fa;
    for (int v : G[u]) {
        if (v == fa)
            continue;
        ch++;
        dfs(v, u);
        lb[u] = min(lb[u], lb[v]);
        rb[u] = max(rb[u], rb[v]);
    }
    if (ch == 0) {
        lb[u] = rb[u] = ++dfs_clock;
        mapping[dfs_clock] = u;
    }
}

void dfs2(int u, int fa) {
    modify(1, 1, dfs_clock, lb[u], rb[u], 1);
    for (int v : G[u]) {
        if (v == fa)
            continue;
        dfs2(v, u);
    }
}

int query(int o, int l, int r) {
    if (l == r)
        return l;
    if (mx[o] == 0)
        return 0;
    int m = (l + r) >> 1;
    push(o);
    if (mx[o << 1] == mx[o])
        return query(o << 1, l, m);
    else
        return query(o << 1 | 1, m + 1, r);
}

int ans;

void up(int u) {
    if (u == 0)
        return;
    if (vis[u])
        return;
    ans++;
    vis[u] = 1;
    modify(1, 1, dfs_clock, lb[u], rb[u], -1);
    up(par[u]);
}

int main() {
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    int N, M;
    scanf("%d%d", &N, &M);
    for (int i = 1; i < N; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    if (M == 0) 
        ans = 1;
    else
        ans = 0;
    dfs(1, 0);
    dfs2(1, 0);
    while (M--) {
        int x = query(1, 1, dfs_clock);
        if (x == 0)
            break;
        up(mapping[x]);
    }
    printf("%d\n", ans - 1);
    return 0;
}
