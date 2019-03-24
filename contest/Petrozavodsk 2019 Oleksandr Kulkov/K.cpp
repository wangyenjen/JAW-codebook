#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 4000 + 7;
const ll MOD = 1000000000 + 7;

ll inv[MAX_N];
ll dp[2][MAX_N];

ll power(ll a, ll n) {
    ll x = 1;
    while (n) {
        if (n & 1)
            x = x * a % MOD;
        a = a * a % MOD;
        n >>= 1;
    }
    return x;
}

int main() {
    int n;
    scanf("%d", &n);
    inv[0] = 1;
    for (int i = 1; i <= n; i++)
        inv[i] = power(i, MOD - 2);
    int cur = 1;
    for (int i = 1; i <= n; i++)
        dp[cur][i] = 1;
    for (int j = 2; j <= n; j++) {
        cur ^= 1;
        for (int i = 1; i <= j; i++) {
            dp[cur][i] = ((i - 3 + MOD) * inv[j - 1] % MOD * dp[cur ^ 1][i - 1] % MOD + (j - i) * inv[j - 1] % MOD * dp[cur ^ 1][i] % MOD) % MOD;
        }
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        int a;
        scanf("%d", &a);
        ans = (ans + dp[cur][i] * a % MOD) % MOD;
    }
    printf("%lld\n", ans);
    return 0;
}
