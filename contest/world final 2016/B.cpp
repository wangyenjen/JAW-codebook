#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
using namespace std;

constexpr int infd = 5'000'0000;
using P = pair<int, int>;

void dijkstra(vector<P> *adj, int n,
              int *d, int start) {
    fill_n(d, n, infd);
    priority_queue<P, vector<P>, greater<P>> pq;
    
    d[start] = 0;
    pq.emplace(0, start);

    while (!pq.empty()) {
        P dvv = pq.top();
        int dv = dvv.first, v = dvv.second;
        pq.pop();
        if (d[v] != dv)
            continue;
        for (P udvu : adj[v]) {
            int u = udvu.first, dvu = udvu.second;
            if (d[u] > d[v] + dvu) {
                d[u] = d[v] + dvu;
                pq.emplace(d[u], u);    
            }
        }
    }
}

vector<P> adj[5000];
vector<P> rev[5000];
int d1[5000];
int d2[5000];
namespace ss { long long s[5001]; }
constexpr long long infdp = 5'000'0000'0000'0000;
long long dp[5000][5001];

void fill_dp(int g, int l, int r, int tl, int tr) {
    using ss::s;

    if (l == r)
        return;

    int n = (l + r) >> 1;

    long long ans = infdp;
    int t = tl;
    for (int i = tl; i < min(n, tr); i++) {
        long long cost = dp[g - 1][i] + (n - i - 1) * (s[n] - s[i]);
        // fprintf(stderr, "dp[%d][%d] <- %lld (i=%d)\n", g, n, cost, i);
        if (cost < ans)
            ans = cost, t = i;
    }
    dp[g][n] = ans;

    fill_dp(g, l, n, tl, t + 1);
    fill_dp(g, n + 1, r, t, tr);
}

long long solve(int n, int m) {
    using ss::s;

    for (int i = 0; i < n; i++)
        s[i + 1] = s[i] + d2[i];
    
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++)
        dp[0][i] = s[i] * (i - 1);
    for (int g = 1; g < m; g++)
        fill_dp(g, 0, n + 1, 1, n);

#if 0
    for (int i = 0; i < n; i++)
        fprintf(stderr, "d2[%d]=%d\n", i, d2[i]);
    for (int g = 0; g < m; g++)
        for (int i = 0; i <= n; i++)
            fprintf(stderr, "dp[%d][%d]=%lld\n", g, i, dp[g][i]);
#endif
    // fprintf(stderr, "GET %d %d\n", m - 1, n);
    return dp[m - 1][n];
}

int main() {
    int n, b, s, r;
    scanf("%d%d%d%d", &n, &b, &s, &r);

    for (int i = 0; i < r; i++) {
        int u, v, d;
        scanf("%d%d%d", &u, &v, &d);
        u--, v--;
        adj[u].emplace_back(v, d);
        rev[v].emplace_back(u, d);
    }

    dijkstra(adj, n, d1, b);
    dijkstra(rev, n, d2, b);
    for (int i = 0; i < n; i++)
        d2[i] += d1[i];

    sort(d2, d2 + b);
    printf("%lld\n", solve(b, s));
}
