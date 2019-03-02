#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100000 + 7;

int dp[MAX_N];
int tag[MAX_N];
int pre[MAX_N];
bool vis[MAX_N];
vector<int> G[MAX_N];
vector<int> G2[MAX_N];

int main() {
    freopen("assassination.in", "r", stdin);
    int n, m, s, t;
    scanf("%d%d%d%d", &n, &m, &s, &t);
    while (m--) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G2[v].push_back(u);
    }

    memset(pre, -1, sizeof(pre));
    pre[s] = 0;
    queue<int> que;
    vis[s] = 1;
    que.push(s);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (int v : G[u]) {
            if (!vis[v]) {
                vis[v] = 1;
                pre[v] = u;
                que.push(v);
            }
        }
    }

    int p = t;
    vector<int> path;
    while (p) {
        path.push_back(p);
        p = pre[p];
    }

    reverse(path.begin(), path.end());
    for (int i = 0; i < (int)path.size(); i++) {
        dp[path[i]] = i + 1;
    }
    
    for (int i = path.size(); i >= 1; i--) {
        que.push(path[i - 1]);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (int v : G2[u]) {
                if (!dp[v]) {
                    dp[v] = i;
                    que.push(v);
                }
            }
        }
    }
    
    for (int u : path) {
        for (int v : G[u]) {
            if (!dp[v])
                continue;
            int a = dp[u];
            int b = dp[v];
            if (a > b)
                continue;
            a++, b--;
            if (a > b)
                continue;
            tag[a]++;
            tag[b + 1]--;
        }
    }

    vector<int> ans;
    for (int i = 1, ss = 0; i <= (int)path.size(); i++) {
        ss += tag[i];
        if (ss == 0 && path[i - 1] != s && path[i - 1] != t)
            ans.push_back(path[i - 1]);
    }


    sort(ans.begin(), ans.end());
    printf("%d\n", (int)ans.size());
    for (int i = 0; i < (int)ans.size(); i++)
        printf("%d%c", ans[i], " \n"[i == (int)ans.size() - 1]);

    return 0;
}
