#include <cstdio>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

constexpr int maxn = 500;
constexpr int mod = 37493;

int stir[501][501], stir2[501];
int fore[501][501];
int dp[501][501];

int depth[maxn]; // non-zero iff visited
vector<int> adj[maxn];
vector<int> cycles;

void dfs(int v, int p, int d) {
    depth[v] = d;
    for (int c : adj[v]) {
        if (c == p)
            continue;
        if (depth[c] == 0) {
            // tree edge
            dfs(c, v, d + 1);
        } else if (depth[c] < depth[v]) {
            // back edge
            cycles.push_back(depth[v] - depth[c] + 1);
        }
    }
}

int solve(int n, int cc/*, vector<int> cycles*/) {
    for (int i = 1; i <= n; i++)
        dp[0][i] = fore[i][cc];

    for (int i = 0; i < (int) cycles.size(); i++) {
        for (int j = 1; j <= n; j++)
            dp[i + 1][j] = (dp[i][j] - dp[i][j - 1] + mod) % mod;
        for (int j = 3; j < (int) cycles[i]; j++) // m
            for (int k = n; k >= 1; k--) // n
                dp[i + 1][k] = (dp[i][k] - dp[i + 1][k - 1] + mod) % mod;
    }

    return dp[cycles.size()][n];
}

int main() {
    freopen("codecircles.in", "r", stdin);
    freopen("codecircles.out", "w", stdout);
    for (int i = 1; i <= maxn; i++) {
        stir[i][1] = 1;
        for (int j = 2; j < i; j++) {
            stir[i][j] = (stir[i - 1][j - 1] + stir[i - 1][j] * j) % mod;
        }
        stir[i][i] = 1;

        stir2[i] = accumulate(stir[i] + 1, stir[i] + i + 1, 0) % mod;
    }

    for (int i = 1; i <= maxn; i++) {
        fore[i][i] = stir2[i];
        for (int j = i - 1; j >= 1; j--)
            fore[i][j] = (fore[i][j + 1] - fore[i - 1][j] + mod) % mod;
    }

#if 0
    cycles = {3, 3};
    printf("%d\n", solve(6, 2));
    return 0;
#endif

    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int cc = 0;
    for (int i = 0; i < n; i++)
        if (depth[i] == 0) {
            cc++;
            dfs(i, -1, 1);
        }
    
#if 0
    fprintf(stderr, "params: n=%d cc=%d cycles={", n, cc);
    for (int i = 0; i < (int) cycles.size(); i++) {
        if (i)
            fprintf(stderr, ", ");
        fprintf(stderr, "%d", cycles[i]);
    }
    fprintf(stderr, "}\n");
#endif

    printf("%d\n", solve(n, cc));
}
