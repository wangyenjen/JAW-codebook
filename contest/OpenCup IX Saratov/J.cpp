#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
#include <string>
using namespace std;

using P = pair<int, string>;

constexpr int inf = 1000000007;
int dp[2012][2012];

vector<P> input() {
    int n;
    scanf("%d", &n);

    vector<P> v;
    v.reserve(n);
    for (int i = 0; i < n; i++) {
        char name[16];
        int d;
        scanf("%15s %d", name, &d);

        v.emplace_back(d, name);
    }

    return move(v);
}

int main() {
    freopen("taxi.in", "r", stdin);

    vector<P> boys = input();
    vector<P> girls = input();

    sort(boys.begin(), boys.end());
    sort(girls.begin(), girls.end());

    int n = boys.size(), m = girls.size();
    
    dp[0][0] = 0;
    fill_n(dp[0] + 1, m, inf);

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            int ans = inf;

            for (int k = 1; k <= min(4, i); k++) {
                for (int l = 0; l <= min(4 - k, j); l++) {
                    int x = boys[i - 1].first;
                    if (l)
                        x = max(x, girls[j - 1].first);

                    x += dp[i - k][j - l];
                    ans = min(ans, x);
                }
            }

            dp[i][j] = ans;
        }
    }
    printf("%d\n", dp[n][m]);

    vector<vector<P>> taxis;
    for (int i = n, j = m; i; ) {
        int ans = inf, bk = 1, bl = 0;

        for (int k = 1; k <= min(4, i); k++) {
            for (int l = 0; l <= min(4 - k, j); l++) {
                int x = boys[i - 1].first;
                if (l)
                    x = max(x, girls[j - 1].first);

                x += dp[i - k][j - l];
                if (x < ans) {
                    ans = x;
                    bk = k;
                    bl = l;
                }
            }
        }

        taxis.emplace_back();
        for (int k = 1; k <= bk; k++)
            taxis.back().push_back(boys[i - k]);
        for (int l = 1; l <= bl; l++)
            taxis.back().push_back(girls[j - l]);

        i -= bk;
        j -= bl;
    }

    printf("%zd\n", taxis.size());
    for (int j = 0; j < (int) taxis.size(); j++) {
        const auto &taxi = taxis[j];
        printf("Taxi %d: ", j + 1);
        for (int i = 0; i < (int) taxi.size(); i++) {
            fputs(taxi[i].second.c_str(), stdout);

            if (i == (int) taxi.size() - 2) {
                fputs(" and ", stdout);
            } else if (i < (int) taxi.size() - 2) {
                fputs(", ", stdout);
            }
        }
        puts(".");
    }
}
