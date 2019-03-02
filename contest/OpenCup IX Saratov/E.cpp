#include <cstdio>
#include <tuple>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

struct KM {
    static const int INF = 0x3f3f3f3f;
    static const int MAX_N = 100 + 7;
    int n;
    int mx[MAX_N], my[MAX_N];
    bool vx[MAX_N], vy[MAX_N];
    int sy[MAX_N], w[MAX_N][MAX_N], lx[MAX_N], ly[MAX_N];

    void init(int _n) {
        n = _n;
        for (int i = 0; i <= n; i++) {
            mx[i] = 0;
            my[i] = 0;
            vx[i] = 0;
            vy[i] = 0;
            sy[i] = 0;
            lx[i] = 0;
            ly[i] = 0;
            for (int j = 0; j <= n; j++)
                w[i][j] = 0;
        }
    }

    void add_edge(int u, int v, int x) {
        w[u][v] = x;
    }

    bool dfs(int x) {
        vx[x] = 1;
        for (int y = 1; y <= n; y++) {
            if (vy[y])
                continue;
            int t = lx[x] + ly[y] - w[x][y];
            if (t == 0) {
                vy[y] = 1;
                if (!my[y] || dfs(my[y])) {
                    mx[x] = y;
                    my[y] = x;
                    return 1;
                }
            }
            else
                sy[y] = min(sy[y], t);
        }
        return 0;
    }

    void modify() {
        int t = INF;
        for (int i = 1; i <= n; i++)
            if (!vy[i])
                t = min(t, sy[i]);
        for (int i = 1; i <= n; i++)
            if (vx[i])
                lx[i]-= t;
        for (int i = 1; i <= n; i++)
            if (vy[i])
                ly[i] += t;
    }

    int solve() {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++)
                lx[i] = max(lx[i], w[i][j]);
        }
        for (int i = 1; i <= n; i++) {
            while (1) {
                for (int j = 1; j <= n; j++) {
                    vx[j] = 0;
                    vy[j] = 0;
                    sy[j] = INF;
                }
                if (dfs(i))
                    break;
                else
                    modify();
            }
        }
        int ans = 0;
        for (int i = 1; i <= n; i++)
            ans += w[i][mx[i]];
        return ans;
    }
} km;

constexpr int inf = 1000000007;
constexpr int maxans = 10000;
using E = pair<int, int>;
vector<E> adj[100];
vector<int> dp[100];
vector<vector<int>> opt[100];
int ans[99];

int get(int i, int j) {
    const auto &v = dp[i];
    if (j < (int) v.size())
        return v[j];
    return v.back() + (j - v.size() + 1);
}
vector<int> &getopt(int i, int j) {
    auto &v = opt[i];
    if (j < (int) v.size())
        return v[j];
    return v.back();
}

pair<int, vector<int>> magic(vector<int> vc, int ce) {
    int ansce = inf;
    vector<int> best;
#if 0
    sort(vc.begin(), vc.end());

    do {
        int x = 0;
        for (int i = 0; i < (int) vc.size(); i++)
            x += get(vc[i], i + (i >= ce));
        if (x < ansce) {
            ansce = x;
            best = vc;
        }
    } while (next_permutation(vc.begin(), vc.end()));

    return make_pair(ansce, move(best));
#else
    int n = vc.size();
    km.init(n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            km.add_edge(i + 1, j + 1, maxans - get(vc[i], j + (j >= ce)));

    ansce = maxans * n - km.solve();

    for (int i = 0; i < n; i++)
        best.push_back(vc[km.my[i + 1] - 1]);
#endif
    return make_pair(ansce, move(best));
}

void dfs(int v, int p) {
    vector<int> vc;

    for (E e : adj[v]) {
        int c = e.first;
        if (c == p)
            continue;
        dfs(c, v);

        vc.push_back(c);
    }

    for (int ce = 0; ce <= (int) vc.size(); ce++) {
        int ansce = inf;
        vector<int> best;

        tie(ansce, best) = magic(vc, ce);

        dp[v].push_back(ansce + ce);
        opt[v].push_back(move(best));
    }
}

void dfs2(int v, int p, int x) {
    auto &vc = getopt(v, x);

    for (E e : adj[v]) {
        int c = e.first;
        if (c == p)
            continue;

        int y = find(vc.begin(), vc.end(), c) - vc.begin();
        if (y >= x)
            y++;
        ans[e.second] = y;
        dfs2(c, v, y);
    }
}

int main() {
    freopen("coloring.in", "r", stdin);

    int n;
    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--, v--;

        adj[u].emplace_back(v, i);
        adj[v].emplace_back(u, i);
    }

    dfs(0, 0);
    printf("%d\n", get(0, adj[0].size()) - int(adj[0].size()) + (n - 1));

    dfs2(0, 0, adj[0].size());

    for (int i = 0; i < n - 1; i++)
        printf("%d%c", ans[i] + 1, i == n - 2 ? '\n' : ' ');
}
