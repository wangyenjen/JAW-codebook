#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

template<typename Container>
int smallest_rotation(Container &v) {
    if (v.empty())
        return 0;
    int n = v.size(), i = 0, j = 1;
    while (i < n && j < n) {
        int k = 0;
        while (k < n && v[(i + k) % n] == v[(j + k) % n])
            k++;

        if (v[(i + k) % n] <= v[(j + k) % n])
            j += k + 1;
        else
            i += k + 1;
        if (i == j)
            j++;
    }
    return (i < n ? i : j);
}
template<typename Container>
int get_cycle(const Container &v) {
    if (v.empty())
        return 0;
    int n = v.size();
    vector<int> z(n);
    z[0] = n;
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        int j = max(min(z[i - l], r - i), 0);
        while (i + j < n && v[i + j] == v[j])
            j++;
        if (j == n - i && (n % i == 0))
            return i;

        z[i] = j;
        if (i + j > r)
            l = i, r = i + j;
    }
    return n;
}

vector<int> adj[100];
vector<int> feat[100];
int rot[100], cyc[100];
vector<pair<int, int>> feat2[100], sfeat2[100];
int g[100];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int nv;
        scanf("%d", &nv);
        adj[i].resize(nv);
        for (int j = 0; j < nv; j++) {
            scanf("%d", &adj[i][j]);
            adj[i][j]--;
        }
    }

    int ng = 1;
    fill_n(g, n, 0);

    while (true) {
        for (int i = 0; i < n; i++) {
            feat[i].clear();
            for (int j : adj[i])
                feat[i].push_back(g[j]);
            rot[i] = smallest_rotation(feat[i]);
            cyc[i] = get_cycle(feat[i]);
        }
        for (int i = 0; i < n; i++) {
            feat2[i].clear();
            for (int j : adj[i]) {
                int idx = find(adj[j].begin(), adj[j].end(), i) - adj[j].begin();
                idx = (idx - rot[j] + adj[j].size()) % cyc[j];
                feat2[i].emplace_back(g[j], idx);
            }
            int rot2 = smallest_rotation(feat2[i]);
            rotate(feat2[i].begin(), feat2[i].begin() + rot2, feat2[i].end());
        }

        copy_n(feat2, n, sfeat2);
        sort(sfeat2, sfeat2 + n);

        int ng2 = unique(sfeat2, sfeat2 + n) - sfeat2;
        if (ng == ng2)
            break;
        ng = ng2;

        for (int i = 0; i < n; i++)
            g[i] = lower_bound(sfeat2, sfeat2 + ng, feat2[i]) - sfeat2;
    }

    vector<vector<int>> ans;
    for (int i = 0; i < ng; i++) {
        ans.emplace_back();
        for (int j = 0; j < n; j++)
            if (g[j] == i)
                ans.back().push_back(j);
        sort(ans.back().begin(), ans.back().end());
    }
    sort(ans.begin(), ans.end());

    bool none = true;
    for (int i = 0; i < ng; i++)
        if (ans[i].size() > 1)
            for (int j = 0; j < (int) ans[i].size(); j++) {
                none = false;
                printf("%d%c", ans[i][j] + 1, j == (int) ans[i].size() - 1 ? '\n' : ' ');
            }
    if (none)
        puts("none");
}
