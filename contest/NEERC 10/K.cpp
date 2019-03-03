#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 9999 + 7;

int deg[MAX_N];
int has[MAX_N];
int ans[MAX_N];
bool done[MAX_N];
vector<int> G[MAX_N];

int main() {
    freopen("kgraph.in", "r", stdin);
    freopen("kgraph.out", "w", stdout);
    int n, m;
    scanf("%d%d", &n, &m);
    while (m--) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }
    int k = 0;
    for (int i = 1; i <= n; i++)
        k = max(k, deg[i]);
    if (k % 2 == 0)
        k++;
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    for (int i = 1; i <= n; i++)
        pq.emplace(deg[i], i);
    vector<int> vs;
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if (done[u])
            continue;
        done[u] = 1;
        vs.push_back(u);
        for (int v : G[u]) {
            deg[v]--;
            if (!done[v])
                pq.emplace(deg[v], v);
        }
    }
    reverse(vs.begin(), vs.end());
    for (int x : vs) {
        for (int y : G[x]) {
            if (!ans[y])
                continue;
            else
                has[ans[y]] = x;
        }
        for (int i = 1; i <= k; i++) {
            if (has[i] == x)
                continue;
            else {
                ans[x] = i;
                break;
            }
        }
    }
    printf("%d\n", k);
    for (int i = 1; i <= n; i++)
        printf("%d\n", ans[i]);
    return 0;
}
