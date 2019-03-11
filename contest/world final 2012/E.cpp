#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 75 + 7;
const int INF = 0x3f3f3f3f;

int cover[MAX_N];
char G[MAX_N][MAX_N];
int dp[MAX_N][1 << 8];
int path[MAX_N][1 << 8];

int main() {
    int n, kcase = 0;
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; i++) {
            scanf("%s", G[i]);
            for (int j = 0; j < n; j++)
                G[i][j] -= '0';
        }
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            bool ok = 1;
            for (int j = 0; j < n; j++) {
                if (j != i && G[i][j] == 0) {
                    ok = 0;
                    break;
                }
            }
            if (ok) {
                ans = {i};
                break;
            }
        }
        if ((int)ans.size()) {
            printf("Case %d: %d %d\n", ++kcase, (int)ans.size(), ans[0] + 1);
            continue;
        }
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                bool ok = 1;
                for (int k = 0; k < n; k++) {
                    if (k == i || k == j)
                        continue;
                    if (G[i][k] == 0 && G[j][k] == 0) {
                        ok = 0;
                        break;
                    }
                }
                if (ok) {
                    ans = {i, j};
                    break;
                }
            }
            if ((int)ans.size())
                break;
        }
        if ((int)ans.size()) {
            printf("Case %d: %d %d %d\n", ++kcase, (int)ans.size(), ans[0] + 1, ans[1] + 1);
            continue;
        }
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    vector<int> ps;
                    for (int l = 0; l < n; l++) {
                        if (l == i || l == j || l == k)
                            continue;
                        ps.push_back(l);
                    }
                    vector<int> vs;
                    for (int l : ps) {
                        if (G[i][l] == 0 && G[j][l] == 0 && G[k][l] == 0) 
                            vs.push_back(l);
                        if ((int)vs.size() > 8)
                            break;
                    }
                    if ((int)vs.size() == 0) {
                        ans = {i, j, k};
                        break;
                    }
                    if ((int)vs.size() > 8)
                        continue;
                    memset(dp, 0x3f, sizeof(dp));
                    memset(path, -1, sizeof(path));
                    dp[0][0] = 0;
                    memset(cover, 0, sizeof(cover));
                    for (int x = 0; x < (int)vs.size(); x++) {
                        for (int y = 0; y < (int)ps.size(); y++) {
                            if (G[ps[y]][x] == 1) 
                                cover[y] |= (1 << x);
                        }
                    }
                    for (int l = 0; l < (int)ps.size(); l++) {
                        for (int s = (1 << (int)vs.size()) - 1; s >= 0; s--) {
                            dp[l + 1][s] = dp[l][s];
                            path[l + 1][s] = 0;
                            if ((s & cover[l]) == cover[l] && dp[l + 1][s] > dp[l][s ^ cover[l]] + 1) {
                                dp[l + 1][s] = dp[l][s ^ cover[l]] + 1;
                                path[l + 1][s] = 1;
                            }
                        }
                    }
                    vector<int> pans = {i, j, k};
                    for (int l = (int)ps.size() - 1, p = (1 << (int)vs.size()) - 1; l >= 0; l--) {
                        if (path[l + 1][p]) {
                            pans.push_back(ps[l]);
                            p ^= cover[l];
                        }
                    }
                    if ((int)ans.size() == 0 || ((int)ans.size() > (int)pans.size()))
                        ans = pans;
                }
                if ((int)ans.size() == 3)
                    break;
            }
            if ((int)ans.size() == 3)
                break;
        }
        sort(ans.begin(), ans.end());
        printf("Case %d: %d", ++kcase, (int)ans.size());
        for (int x : ans)
            printf(" %d", x + 1);
        puts("");
    }
    return 0;
}
