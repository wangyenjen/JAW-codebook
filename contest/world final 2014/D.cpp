#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 25 + 1;
const int INF = 0x3f3f3f3f;

int dp[MAX_N][MAX_N];
vector<int> G[MAX_N];
vector<int> G2[MAX_N];
vector<pair<int, int> > rev[MAX_N];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        G[i].reserve(m);
        G2[i].reserve(m);
        while (m--) {
            int x = 0;
            string s;
            cin >> s;
            for (char c : s)
                x |= (1 << (c - 'a'));
            G[i].push_back(x);
            G2[i].push_back(0);
            for (int j = 0; j < n; j++) {
                if (x & (1 << j)) {
                    rev[j].emplace_back(i, (int)G[i].size() - 1);
                }
            }
        }
    }
    memset(dp, 0x3f, sizeof(dp));
    for (int ed = 0; ed < n; ed++) {
        dp[ed][ed] = 0;
        queue<int> que;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < (int)G[i].size(); j++) {
                G2[i][j] = G[i][j];
            }
        }
        que.push(ed);
        while (!que.empty()) {
            int v = que.front();
            que.pop();
            for (auto p : rev[v]) {
                int u = p.first;
                int i = p.second;
                if (dp[u][ed] != INF)
                    continue;
                G2[u][i] &= ~(1 << v);
                if (G2[u][i] == 0) {
                    dp[u][ed] = dp[v][ed] + 1;
                    que.push(u);
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << (dp[i][j] == INF ? -1 : dp[i][j]) << " \n"[j == n - 1];
    }

    return 0;
}

