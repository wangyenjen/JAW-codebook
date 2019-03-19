#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll INF64 = 1e12;

struct MCMF {
    static const int MAXV = 2000000 + 7;

    struct Edge {
        int v, cap;
        ll w;
        int rev;

        Edge() {}
        Edge(int t2, int t3, ll t4, int t5) : v(t2), cap(t3), w(t4), rev(t5) {}
    };

    int V, s, t;
    vector<Edge> g[MAXV];

    void init(int n) {
        V = n + 2;
        s = n + 1;
        t = n + 2;
        for (int i = 0; i <= V; i++)
            g[i].clear();
    }

    void add_edge(int a, int b, int cap, ll w) {
        g[a].push_back(Edge(b, cap, w, (int)g[b].size()));
        g[b].push_back(Edge(a, 0, -w, (int)g[a].size() - 1));
    }

    ll d[MAXV];
    int id[MAXV], mom[MAXV];
    bool inqu[MAXV];
    queue<int> q;

    ll solve() {
        int mxf = 0;
        ll mnc = 0;
        while (1) {
            fill(d, d + 1 + V, INF64);
            fill(inqu, inqu + 1 + V, 0);
            fill(mom, mom + V + 1, -1);
            mom[s] = s;
            d[s] = 0;
            q.push(s);
            inqu[s] = 1;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                inqu[u] = 0;
                for (int i = 0; i < (int)g[u].size(); i++) {
                    Edge &e = g[u][i];
                    int v = e.v;
                    if (e.cap > 0 && d[v] > d[u] + e.w) {
                        d[v] = d[u] + e.w;
                        mom[v] = u;
                        id[v] = i;
                        if (!inqu[v]) {
                            q.push(v);
                            inqu[v] = 1;
                        }
                    }
                }
            }
            if (mom[t] == -1)
                break;
            int df = INF;
            for (int u = t; u != s; u = mom[u]) 
                df = min(df, g[mom[u]][id[u]].cap);
            for (int u = t; u != s; u = mom[u]) {
                Edge &e = g[mom[u]][id[u]];
                e.cap -= df;
                g[e.v][e.rev].cap += df;
            }
            mxf += df;
            mnc += df * d[t];
        }
        return mnc;
    }
} flow;

const int MAX_N = 100 + 7;

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    n++;
#define A(x) (x)
#define B(x) (x + n)
#define S (n + n + 1)
#define T (n + n + 2)
    flow.init(n << 1);
    flow.add_edge(S, A(1), k, 0);
    for (int i = 1; i <= n; i++) {
        if (i == 1)
            flow.add_edge(A(i), B(i), k - 1, 0);
        flow.add_edge(A(i), B(i), 1, -INF64);
        flow.add_edge(B(i), T, k, 0);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int x;
            scanf("%d", &x);
            flow.add_edge(B(i), A(j), k, x);
        }
    }
    ll ans = flow.solve() + 1ll * n * INF64;
    printf("%lld\n", ans);
    return 0;
}
