#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 20 + 1;
const int INF = 0x3f3f3f3f;

int G[MAX_N][MAX_N];
int dp1[1 << MAX_N][MAX_N]; // 1. 0 -> A        3.  B    -> 0
int dp2[1 << MAX_N][MAX_N]; // 2. B -> n - 1    4. n - 1 -> A

void build_dp(int n, int dp[1 << MAX_N][MAX_N]) {
    for (int s = 1; s < (1 << n); s++) {
        for (int t = 0; t < n; t++) {
            if (dp[s][t] == INF)
                continue;
            for (int i = 0; i < n; i++) {
                if (~s & (1 << i))
                    dp[s | (1 << i)][i] = min(dp[s | (1 << i)][i], dp[s][t] + G[t][i]);
            }
        }
    }
}

int main() {
    int kcase = 0, n, m;
    while (scanf("%d%d", &n, &m) != EOF) {
        memset(G, 0x3f, sizeof(G));
        while (m--) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            G[u][v] = min(G[u][v], w);
            G[v][u] = min(G[v][u], w);
        }

        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++)
                    G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
            }
        }

        if (n == 3) {
            printf("Case %d: %d\n", ++kcase, 2 * G[0][1] + 2 * G[1][2]);
            continue;
        }

        memset(dp1, 0x3f, sizeof(dp1));
        dp1[1 << 0][0] = 0;
        build_dp(n, dp1);

        memset(dp2, 0x3f, sizeof(dp2));
        dp2[1 << (n - 1)][n - 1] = 0;
        build_dp(n, dp2);

        m = (n - 2) / 2;
        int ans = INF;
        for (int s = 0; s < (1 << n); s++) {
            if (s & (1 << 0))
                continue;
            if (s & (1 << (n - 1)))
                continue;
            if (__builtin_popcount(s) != m)
                continue;
            int t = ((1 << n) - 1) ^ s ^ (1 << 0) ^ (1 << (n - 1));
            for (int i = 0; i < n; i++) {
                if (i == 0)
                    continue;
                if (~s & (1 << i))
                    continue;
                for (int j = 0; j < n; j++) {
                    if (j == n - 1)
                        continue;
                    if (~t & (1 << j))
                        continue;

                    int tans = 0;
                    tans += dp1[s | (1 << 0)][i];
                    tans += dp2[t | (1 << (n - 1)) | (1 << i)][i];
                    tans += dp2[s | (1 << (n - 1)) | (1 << j)][j];
                    tans += dp1[t | (1 << 0)][j];
                    
                    ans = min(ans, tans);
                }
            }
        }
        printf("Case %d: %d\n", ++kcase, ans);
    }
    return 0;
}
