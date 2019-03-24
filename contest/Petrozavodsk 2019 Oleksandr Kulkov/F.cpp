#include <cstdio>
#include <numeric>
#include <algorithm>
#include <vector>
using namespace std;

struct E {
    int t, u, v, w;
    void read() {
        scanf("%d%d%d%d", &t, &u, &v, &w);
        u--, v--;
    }
};

struct Ds {
    int p[100000], sz[100000];
    vector<int> c[100000];

    void init(int n) {
        iota(p, p + n, 0);
        for (int i = 0; i < n; i++)
            c[i] = {i}, sz[i] = 1;
    }

    int find(int u) {
        if (u == p[u])
            return u;
        return p[u] = find(p[u]);
    }

    void merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v)
            return;

        if (c[u].size() < c[v].size())
            swap(u, v);
        c[u].insert(c[u].end(), c[v].begin(), c[v].end());
        c[v].clear();
        
        p[v] = u;
        sz[u] += sz[v];
    }
} dj1, dj2;

E e[100000];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++)
        e[i].read();
    sort(e, e + m, [](E l, E r) { return l.w > r.w; });

    dj1.init(n);
    dj2.init(n);
    for (int i = 0, j = 0; i < m; i = j) {
        for (j = i; j < m && e[j].w == e[i].w; j++) {
            dj1.merge(e[j].u, e[j].v);
            if (e[j].t == 1) 
                dj2.merge(e[j].u, e[j].v);
        }
        for (j = i; j < m && e[j].w == e[i].w; j++) {
            int u = dj1.find(e[j].u);
            int u2 = dj2.find(e[j].u);
            if (dj1.sz[u] != dj2.sz[u2])
                dj1.c[u].clear();
        }
    }
    
    vector<int> v;
    for (int i = 0; i < n; i++)
        v.insert(v.end(), dj1.c[i].begin(), dj1.c[i].end());

    sort(v.begin(), v.end());

    printf("%zd\n", v.size());
    for (int i = 0; i < (int) v.size(); i++)
        printf("%d%c", v[i] + 1, i == (int) v.size() - 1 ? '\n' : ' ');
}
