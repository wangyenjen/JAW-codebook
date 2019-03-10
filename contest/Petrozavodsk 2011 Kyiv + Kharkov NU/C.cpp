#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

vector<int> adj[300000];
int h[300000], hp[300000];
int ans[300000];

void dfs1(int v, int p) {
    h[v] = 1;
    for (int c : adj[v])
        if (c != p) {
            dfs1(c, v);
            h[v] = max(h[v], h[c] + 1);
        }
}

void dfs2(int v, int p) {
    vector<int> vec;
    for (int c : adj[v])
        vec.push_back(c != p ? h[c] : hp[v]);
    sort(vec.begin(), vec.end(), greater<int>());

    for (int i = 0; i < (int) vec.size(); i++)
        ans[vec[i]] = max(ans[vec[i]], i + 1);

    int max1 = vec.empty() ? 0 : vec.front(), max2 = vec.size() < 2 ? 0 : vec[1];
    for (int c : adj[v])
        if (c != p) {
            hp[c] = 1 + (h[c] == max1 ? max2 : max1);
            dfs2(c, v);
        }
}

int main() {
    freopen("amoeba.in", "r", stdin);
    // freopen("amoeba.out", "w", stdout);

    int n, a, b;
    scanf("%d%d%d", &n, &a, &b);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs1(0, 0);
    dfs2(0, 0);

#if 0
    for (int i = 0; i < n; i++)
        fprintf(stderr, "hp[%d]=%d\n", i, hp[i]);
#endif

    for (int i = n - 2; i >= 0; i--)
        ans[i] = max(ans[i + 1], ans[i]);

    for (int i = a; i <= b; i++)
        printf("%d\n", ans[i]);
}
