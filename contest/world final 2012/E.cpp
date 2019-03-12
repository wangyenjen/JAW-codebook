#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 75 + 7;
const int INF = 0x3f3f3f3f;

int n, ans;
int vans[MAX_N];
bitset<MAX_N> G[MAX_N];

int read01() {
    char c = 0;
    while (c != '0' && c != '1')
        c = getchar();
    return c - '0';
}

bool dfs(int u, int step, bitset<MAX_N> mask) {
    if (step >= ans)
        return (int)mask.count() == n;
    for (int i = u; i <= n; i++) {
        if (dfs((vans[step] = i) + 1, step +1, mask | G[i]))
            return 1;
    }
    return 0;
}

int main() {
    int kcase = 0;
    while (scanf("%d", &n) == 1) {
        for (int i = 1; i <= n; i++) {
            G[i].reset();
            for (int j = 1; j <= n; j++)
                G[i][j] = read01();
            G[i][i] = 1;
        }
        bitset<MAX_N> mask;
        mask.reset();
        for (ans = 1; ans <= 6; ans++) {
            if (dfs(1, 0, mask))
                break;
        }
        printf("Case %d: %d ", ++kcase, ans);
        for (int i = 0; i < ans; i++)
            printf("%d%c", vans[i], " \n"[i == ans - 1]);
    }
    return 0;
}
