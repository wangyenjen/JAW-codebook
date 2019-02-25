#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100000 + 7;

vector<int> G[MAX_N], G2[MAX_N];
int sz[MAX_N], bcc[MAX_N], bcc_id;
int pre[MAX_N], low[MAX_N], dfs_clock, is_cut[MAX_N];

int dfs(int u, int fa) {
    low[u] = pre[u] = ++dfs_clock;
    int ch = 0;
    for (int v : G[u]) {
        if (v == fa)
            continue;
        if (pre[v])
            low[u] = min(low[u], pre[v]);
        else { 
            ch++;
            low[u] = min(low[u], dfs(v, u));
            if (low[v] >= pre[u]) 
                is_cut[u] = 1;
        }
    }

    if (ch == 1 && fa == 0)
        is_cut[u] = 0;

    return low[u];
}

void dfs2(int u) {
    sz[bcc_id]++;
    bcc[u] = bcc_id;
    for (int v : G[u]) {
        if (!bcc[v])
            dfs2(v);
    }
}


int main() {
    int N, kcase = 0;
    while (scanf("%d", &N) != EOF) {
        if (N == 0)
            break;
        map<int, int> table;
        int node_id = 0;
        for (int i = 0; i <= N * 2; i++) {
            G[i].clear();
            G2[i].clear();
            sz[i] = 0;
            bcc[i] = 0;
            pre[i] = 0;
            bcc[i] = 0;
            low[i] = 0;
            is_cut[i] = 0;
        }
        bcc_id = 0;
        dfs_clock = 0;
        while (N--) {
            int x, y;
            scanf("%d%d", &x, &y);
            if (!table.count(x))
                table[x] = ++node_id;
            if (!table.count(y))
                table[y] = ++node_id;
            x = table[x];
            y = table[y];
            G[x].push_back(y);
            G[y].push_back(x);
        }
        N = node_id;
        for (int i = 1; i <= N; i++) {
            if (!pre[i])
                dfs(i, 0);
        }
        for (int i = 1; i <= N; i++) {
            if (is_cut[i]) {
                bcc[i] = ++bcc_id;
                sz[bcc_id] = 1;
            }
        }
        for (int i = 1; i <= N; i++) {
            if (!bcc[i]) {
                ++bcc_id;
                dfs2(i);
            }
        }
        for (int u = 1; u <= N; u++) {
            for (int v : G[u]) {
                if (bcc[u] != bcc[v]) {
                    G2[bcc[u]].push_back(bcc[v]);
                    G2[bcc[v]].push_back(bcc[u]);
                }
            }
               
        }
        for (int i = 0; i <= bcc_id; i++) {
            sort(G2[i].begin(), G2[i].end());
            G2[i].erase(unique(G2[i].begin(), G2[i].end()), G2[i].end());
        }

        if (bcc_id == 1) {
            printf("Case %d: %d %lld\n", ++kcase, 2, 1ll * N * (N - 1) / 2);
        }
        else {
            int ans1 = 0;
            long long ans2 = 1;
            for (int i = 1; i <= bcc_id; i++) {
                if ((int)G2[i].size() == 1) {
                    ans1++;
                    ans2 *= sz[i];
                }
            }
            printf("Case %d: %d %lld\n", ++kcase, ans1, ans2);
        }
    }

    return 0;
}
