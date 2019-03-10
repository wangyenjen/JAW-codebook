#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100000 + 7;

int dp[MAX_N];

void build_dp(int N) {
    for (int i = 1; i <= N - 1; i++)
        dp[i] = 0;
    dp[N] = 1;
    for (int i = N + 1; i <= 100000; i++) {
        unordered_set<int> st;
        for (int j = 1; j * j <= i; j++) {
            int x = i / j;
            int y = i % j;
            st.insert(((y % 2) * dp[x + 1]) ^ (((j + y) % 2) * dp[x]));
        }
        for (int j = 1; j * j <= i; j++) {
            int x = i % j;
            int y = (i - x * (j + 1)) / j;
            if (y >= 0) {
                st.insert(((x % 2) * dp[j + 1]) ^ ((y % 2) * dp[j]));
                x += j;
                y -= j + 1;
                if (y >= 0) 
                    st.insert(((x % 2) * dp[j + 1]) ^ ((y % 2) * dp[j]));
            }
        }
        for (int j = 0; ; j++) {
            if (st.count(j))
                continue;
            dp[i] = j;
            break;
        }
    }
}

int main() {
    freopen("nimg.in", "r", stdin);
    freopen("nimg.out", "w", stdout);
    int R, F;
    scanf("%d%d", &R, &F);
    build_dp(F);
    for (int times = 1; times <= R; times++) {
        int N;
        scanf("%d", &N);
        int sg = 0;
        while (N--) {
            int x;
            scanf("%d", &x);
            sg ^= dp[x];
        }
        printf("%d%c", sg ? 1 : 0, " \n"[times == R]);
    }
    return 0;
}
