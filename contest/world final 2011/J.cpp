#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
constexpr int maxc = 1000000;
constexpr int vsize = 320;
pair<int, int> v[vsize];
unsigned short dp[vsize + 1][maxc + 1];

void init_v() {
    int n = 0;
    for (int i = 2; ; i++) {
        int x = i * (i + 1) * (2 * i + 1) / 6;
        if (x <= maxc)
            v[n++] = make_pair(x, i);
        else
            break;
    }
    for (int i = 2; ; i++) {
        int x = 2 * i * (i + 1) * (2 * i + 1) / 3;
        if (x <= maxc)
            v[n++] = make_pair(x, -(2 * i));
        else
            break;
    }
    for (int i = 2; ; i++) {
        int x = i * (2 * i - 1) * (2 * i + 1) / 3;
        if (x <= maxc)
            v[n++] = make_pair(x, -(2 * i - 1));
        else
            break;
    }

    sort(v, v + vsize);
}
void init_dp() {
    fill_n(dp[0] + 1, maxc, vsize + 1);
    for (int i = 0; i < vsize; i++) {
        copy_n(dp[i], v[i].first, dp[i + 1]);
        for (int j = v[i].first; j <= maxc; j++)
            dp[i + 1][j] = min(dp[i][j - v[i].first] + 1, (int) dp[i][j]);
    }
}

void solve(int c, int t) {
    int n = dp[vsize][c];
    if (n > vsize) {
        printf("Case %d: impossible\n", t);
        return;
    }
    printf("Case %d:", t);

    for (int i = vsize - 1; i >= 0; i--) {
        if (c >= v[i].first && dp[i][c - v[i].first] == n - 1) {
            int x = v[i].second;
            if (x > 0)
                printf(" %dH", x);
            else
                printf(" %dL", -x);
            c -= v[i].first;
            n--;
        }
    }

    putchar('\n');
}

int main() {
    init_v();
    init_dp();

    for (int t = 1, c; scanf("%d", &c), c; t++) {
        solve(c, t);
    }
}
