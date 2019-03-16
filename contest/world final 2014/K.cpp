#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAX_N = 3000000 + 7;
const int LOG = 23;

int dp[MAX_N][LOG];
vector<int> G[MAX_N];

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    int best = 0;
    for (int i = 0; i < k; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        if (r < l) {
            best = max(best, r);
            r += n;
        }
        G[l].push_back(r);
    }
    for (int l = 1; l <= n; l++) {
        for (int r : G[l]) {
            best = max(best, r);
        }
        if (best < l)
            continue;
        int t = best - l;
        for (int i = 0; i < 3; i++) {
            int t2 = min(n + n + n + 1, l + i * n + t + 1);
            dp[i * n + l][0] = t2;
        }
    }
    for (int j = 0; j < LOG; j++)
        dp[n + n + n + 1][j] = n + n + n + 1;
    for (int j = 1; j < LOG; j++) {
        for (int i = 1; i <= n + n + n; i++)
            dp[i][j] = dp[dp[i][j - 1]][j - 1];
    }
#if 0
    for (int i = 1; i <= 10; i++) {
        for (int j = 0; j < LOG; j++)
            printf("%d ", dp[i][j]);
        puts("");
    }
#endif
    int ans = INF;
    for (int i = 1; i <= n; i++) {
        if (dp[i][LOG - 1] == 0)
            continue;
        int pans = 1, p = i;
        int t = n + i;
        for (int j = LOG - 1; j >= 0; j--) {
            if (dp[p][j] < t) {
                pans += (1 << j);
                p = dp[p][j];
            }
        }
        ans = min(ans, pans);
    }
    if (ans == INF)
        puts("impossible");
    else
        printf("%d\n", ans);
    return 0;
}

