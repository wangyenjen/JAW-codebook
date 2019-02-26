#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

typedef pair<ll, ll> Data;

const Data BASE = make_pair(31, 37);
const Data MOD = make_pair(1000000000 + 7, 1000000000 + 9);

const int MAX_N = 1000000 + 7;

Data operator + (const Data &a, const Data &b) {
    return make_pair((a.first + b.first) % MOD.first, (a.second + b.second) % MOD.second);
}

Data operator - (const Data &a, const Data &b) {
    return make_pair((a.first - b.first + MOD.first) % MOD.first, (a.second - b.second + MOD.second) % MOD.second);
}

Data operator * (const Data &a, const Data &b) {
    return make_pair(a.first * b.first % MOD.first, a.second * b.second % MOD.second);
}

int dp[MAX_N][2];
Data power[MAX_N];
int deg_in[MAX_N];
int deg_out[MAX_N];
vector<int> G[MAX_N];

void dfs(int u) {
    dp[u][0] = 0;
    dp[u][1] = 1;
    for (int v : G[u]) {
        dfs(v);
        dp[u][0] += max(dp[v][0], dp[v][1]);
        dp[u][1] += dp[v][0];
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    power[0] = make_pair(1, 1);
    for (int i = 1; i < MAX_N; i++)
        power[i] = power[i] * BASE;

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        int mx_id = 0;
        map<Data, int> mp;
        vector<string> vs;
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            vs.push_back(s);
            Data hv = make_pair(0, 0);
            for (int j = 0; j < (int)s.size(); j++) {
                hv = hv * BASE + make_pair(s[j] - 'a' + 1, s[j] - 'a' + 1);
                if (!mp.count(hv))
                    mp[hv] = ++mx_id;
            }
        }
        for (int i = 1; i <= mx_id; i++) {
            deg_in[i] = 0;
            deg_out[i] = 0;
            G[i].clear();
            dp[i][0] = dp[i][1] = 0;
        }
        for (int i = 0; i < n; i++) {
            string &s = vs[i];
            Data hv = make_pair(0, 0);
            Data hv2 = make_pair(0, 0);
            for (int j = 0; j < (int)s.size(); j++) {
                hv = hv * BASE + make_pair(s[j] - 'a' + 1, s[j] - 'a' + 1);
                if (j > 0)
                    hv2 = hv2 * BASE + make_pair(s[j] - 'a' + 1, s[j] - 'a' + 1);
                if (j > 0 && mp.count(hv2)) {
                    G[mp[hv2]].push_back(mp[hv]);
                    deg_in[mp[hv]]++;
                    deg_out[mp[hv2]]++;
                }
            }
        }
        for (int i = 1; i <= mx_id; i++) {
            sort(G[i].begin(), G[i].end());
            G[i].erase(unique(G[i].begin(), G[i].end()), G[i].end());
        }
        int ans = 0;
        for (int i = 1; i <= mx_id; i++) {
            if (deg_in[i] == 0) {
                dfs(i);
                ans += max(dp[i][0], dp[i][1]);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
