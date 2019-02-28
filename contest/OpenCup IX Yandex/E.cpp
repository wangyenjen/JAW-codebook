#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 20 + 1;
const int INF = 0x3f3f3f3f;

int dp[1 << MAX_N];
vector<int> G[MAX_N];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<pair<int, int> > es;
    while (m--) {
        int  a, b;
        scanf("%d%d", &a, &b);
        a--, b--;
        G[a].push_back(b);
        G[b].push_back(a);
        es.emplace_back(a, b);
    }
    for (int i = 1; i < (1 << n); i++) {
        dp[i] = INF;
        for (int a = 0; a < n; a++) {
            if (~i & (1 << a))
                continue;
            for (int b : G[a]) {
                if (~i & (1 << b))
                    continue;
                dp[i] = min(dp[i], dp[i ^ (1 << a)] + 2);
                dp[i] = min(dp[i], dp[i ^ (1 << b)] + 2);
                dp[i] = min(dp[i], dp[i ^ (1 << a) ^ (1 << b)] + 2);
            }
        }
    }
    int ans = INF;
    for (int i = 0; i < (1 << n); i++) {
        int cost = dp[i];
        for (auto e : es) {
            if ((~i & (1 << e.first)) && (~i & (1 << e.second)))
                cost++;
        }
        ans = min(ans, cost);
    }
    printf("%d\n", ans);
    return 0;
}
