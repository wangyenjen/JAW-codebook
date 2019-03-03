#include <cstdio>
#include <algorithm>
#include <vector>
#include <tuple>
using namespace std;

constexpr int inf = 1000000007;
vector<pair<int, int>> adj[100000];

int dist[100000];
int vec[100000];

void bfs(int n, int t) {
    fill_n(dist, n, inf);

    int qb = 0, qe = 0;
    dist[t] = 0;
    vec[qe++] = t;

    while (qb < qe) {
        int v = vec[qb++];

        for (auto p : adj[v])
            if (dist[p.first] >= inf) {
                dist[p.first] = dist[v] + 1;
                vec[qe++] = p.first;
            }
    }
}

int main() {
#ifndef LOCAL
    freopen("ideal.in", "r", stdin);
    freopen("ideal.out", "w", stdout);
#endif

    int n, m;
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        u--, v--;
        adj[u].emplace_back(v, c);
        adj[v].emplace_back(u, c);
    }

    // s = 0, t = n - 1
    bfs(n, n - 1);

    printf("%d\n", dist[0]);

    vector<int> candi = {0};
    for (int d = dist[0]; d; d--) {
        int opt = inf;
        vector<int> can2;

        for (int v : candi)
            for (auto p : adj[v])
                if (dist[p.first] < d) {
                    if (p.second < opt)
                        opt = p.second, can2 = { p.first };
                    else if (p.second == opt)
                        can2.push_back(p.first);
                }

        sort(can2.begin(), can2.end());
        can2.erase(unique(can2.begin(), can2.end()), can2.end());

        candi = move(can2);
        printf("%d%c", opt, d == 1 ? '\n' : ' ');
    }
}
