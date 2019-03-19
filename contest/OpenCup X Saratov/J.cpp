#include <cstdio>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
constexpr int maxn = 100000;
vector<pair<int, int>> adj[maxn];
int t[maxn], k[maxn];

long long loss[maxn], sumt[maxn], sumk[maxn];
vector<int> ans[maxn];

void dfs(int v, int p) {
    vector<tuple<long long, long long, int>> vec;
    sumk[v] = sumt[v] = loss[v] = 0;

    vec.emplace_back(k[v], t[v], v);
    loss[v] += k[v] * t[v];

    for (auto [c, d] : adj[v]) {
        // fprintf(stderr, "v=%d c=%d d=%d\n", v, c, d);
        if (c == p)
            continue;
        dfs(c, v);

        vec.emplace_back(sumk[c], sumt[c] + 2 * d, c);
        loss[v] += d * sumk[c] + loss[c];
    }

    sort(vec.begin(), vec.end(), [](auto l, auto r) {
        auto [kl, tl, il] = l;
        auto [kr, tr, ir] = r;
        (void) il, (void) ir;
        return kl * tr > kr * tl;
    });

    for (auto [kk, tt, ii] : vec) {
        // fprintf(stderr, "v=%d ii=%d; ", v, ii);
        ans[v].push_back(ii);
        loss[v] += sumt[v] * kk;
        sumk[v] += kk;
        sumt[v] += tt;
    }

    // fprintf(stderr, "v=%d loss=%lld sumk=%lld sumt=%lld\n", v, loss[v], sumk[v], sumt[v]);
}

void dfs2(int v) {
    for (int c : ans[v]) {
        if (c == v) {
            printf("P %d\n", v + 1);
        } else {
            printf("M %d\n", c + 1);
            dfs2(c);
            printf("M %d\n", v + 1);
        }
    }
}

int main() {
    freopen("beetles.in", "r", stdin);
    freopen("beetles.out", "w", stdout);
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", t + i);
    for (int i = 0; i < n; i++)
        scanf("%d", k + i);
    for (int i = 0; i < n - 1; i++) {
        int u, v, d;
        scanf("%d%d%d", &u, &v, &d);
        u--, v--;
        adj[u].emplace_back(v, d);
        adj[v].emplace_back(u, d);
        // fprintf(stderr, "u=%d v=%d d=%d\n", u, v, d);
    }

    dfs(0, -1);
    printf("%lld\n", loss[0]);
    dfs2(0);
}
