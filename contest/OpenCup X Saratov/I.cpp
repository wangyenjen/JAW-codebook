#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100000 + 7;

char S[MAX_N];
int val[MAX_N];
int dep[MAX_N];
int par[MAX_N];
int best, st, ed;
vector<int> G[MAX_N];
set<tuple<int, int, int> > bst[MAX_N];

void dfs(int u, int fa = 0) {
    int now_val = (S[u] == 'L' ? -1 : 1);
    val[u] = val[fa] + now_val;
    dep[u] = dep[fa] + 1;
    par[u] = fa;
    for (int v : G[u]) {
        if (v == fa)
            continue;
        dfs(v, u);
        if ((int)bst[u].size() < (int)bst[v].size())
            swap(bst[u], bst[v]);
        for (auto x : bst[v]) {
            int a = get<2>(x);
            auto it = bst[u].lower_bound(make_tuple(2 * val[u] - get<0>(x) - now_val, -MAX_N, -MAX_N));
            if (it == bst[u].end())
                continue;
            int b = get<2>(*it);
            if (get<0>(*it) ==2 * val[u] - get<0>(x) - now_val) {
                if (dep[a] + dep[b] - 2 * dep[u] > best) {
                    best = dep[a] + dep[b] - 2 * dep[u] + 1;
                    st = a;
                    ed = b;
                }
            }
        }
        for (auto x : bst[v])
            bst[u].insert(x);
    }
    auto it = bst[u].lower_bound(make_tuple(val[fa], -MAX_N, -MAX_N));
    if (it != bst[u].end()) {
        int a = get<2>(*it);
        if (get<0>(*it) == val[fa]) {
            if (dep[a] - dep[fa] > best) {
                best = dep[a] - dep[fa];
                st = a;
                ed = u;
            }
        }
    }
    bst[u].emplace(val[u], -dep[u], u);
}

int main() {
    freopen("shoes.in", "r", stdin);
    freopen("shoes.out", "w", stdout);
    int n;
    scanf("%d", &n);
    scanf("%s", S + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1);
    printf("%d\n", best);
    if (best == 0)
        return 0;
    vector<int> v1, v2;
    int u = st, v = ed;
    while (1) {
        if (dep[u] > dep[v]) 
            v1.push_back(u);
        else 
            v2.push_back(v);
        if (u == v)
            break;
        if (dep[u] > dep[v])
            u = par[u];
        else
            v = par[v];
    }
    reverse(v2.begin(), v2.end());
    vector<int> ans;
    for (int x : v1)
        ans.push_back(x);
    for (int x : v2)
        ans.push_back(x);
    for (int i = 0; i < (int)ans.size(); i++)
        printf("%d%c", ans[i], " \n"[i == (int)ans.size() - 1]);
    return 0;
}
