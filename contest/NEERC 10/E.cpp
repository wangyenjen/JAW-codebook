#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 4000 + 7;
const ll INF64 = 0x3f3f3f3f3f3f3f3fll;

int ans[MAX_N];
ll dp[MAX_N][MAX_N];
int path[MAX_N][MAX_N];
pair<int, int> A[MAX_N], B[MAX_N];

int main() {
    freopen("evacuation.in", "r", stdin);
    freopen("evacuation.out", "w", stdout);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &A[i].first);
        A[i].second = i;
    }
    int m;
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d", &B[i].first);
        B[i].second = i;
    }
    sort(A + 1, A + n + 1);
    sort(B + 1, B + m + 1);
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (dp[i - 1][j - 1] + abs(B[i].first - A[j].first) < dp[i][j]) {
                dp[i][j] = dp[i - 1][j - 1] + abs(B[i].first - A[j].first);
                path[i][j] = i - 1;
            }
            if (dp[i][j - 1] + abs(B[i].first - A[j].first) < dp[i][j]) {
                dp[i][j] = dp[i][j - 1] + abs(B[i].first - A[j].first);
                path[i][j] = i;
            }
        }
    }
    printf("%lld\n", dp[m][n]);
    for (int i = m, j = n; j >= 1; i = path[i][j], j--) 
        ans[A[j].second] = B[i].second;
    for (int i = 1; i <= n; i++)
        printf("%d%c", ans[i], " \n"[i == n]);
    return 0;
}
