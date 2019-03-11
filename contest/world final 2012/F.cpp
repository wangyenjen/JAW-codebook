#include <bits/stdc++.h>

using namespace std;

struct Dinic {
    static const int MXN=  100000 + 7;
    
    struct Edge {
        int v, f, re;
    };
    
    int n, s, t, level[MXN];
    vector<Edge> E[MXN];

    void init(int _n, int _s, int _t) {
        n = _n;
        s = _s;
        t = _t;
        for (int i = 0; i < n; i++)
            E[i].clear();
    }

#define SZ(x) ((int)(x).size())
#define PB push_back
    void add_edge(int u, int v, int f) {
        E[u].PB({v, f, SZ(E[v])}); 
        E[v].PB({u, 0, SZ(E[u]) - 1});
    }

    bool bfs() {
        for (int i = 0; i < n; i++)
            level[i] = -1;
        queue<int> que;
        que.push(s);
        level[s] = 0;
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (auto it : E[u]) {
                if (it.f > 0 && level[it.v] == -1) {
                    level[it.v] = level[u] + 1;
                    que.push(it.v);
                }
            }
        }
        return level[t] != -1;
    }

    int dfs(int u, int nf) {
        if (u == t)
            return nf;
        int res = 0;
        for (auto &it : E[u]) {
            if (it.f > 0 && level[it.v] == level[u] + 1) {
                int tf = dfs(it.v, min(nf, it.f));
                res += tf;
                nf -= tf;
                it.f -= tf;
                E[it.v][it.re].f += tf;
                if (nf == 0)
                    return res;
            }
        }
        if (!res)
            level[u] = -1;
        return res;
    }

    int flow(int res = 0) {
        while (bfs())
            res += dfs(s, 0x7fffffff);
        return res;
    }
};

struct Dsu {
    int par[1000000], cc;

    void init(int n) {
        cc = n;
        for (int i = 0; i < n; i++)
            par[i] = i;
    }

    int find(int x) {
        if (x == par[x])
            return x;
        else
            return par[x] = find(par[x]);
    }

    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y)
            return 0;
        if(x < y)
            swap(x, y);
        par[y] = x;
        cc--;
        return 1;
    }
};

Dinic dinic;
int main() {
    int t = 0;
    while(1){
        int adj[54][54];
        char tmp[10];
        bool meow[54];
        memset(meow, 0, sizeof(meow));
        for(int i = 0; i < 54; i++)
            for(int j = 0; j < 54; j++)
                adj[i][j] = 0;
        int AA = 0, BB = 0;
        while(1){
            int flag = scanf("%s", tmp);
            if(flag != 1)
                return 0;
            if(tmp[0] == '0')
                break;
            int u, v;
            if(tmp[0] >= 'a' && tmp[0] <= 'z')
                u = tmp[0] - 'a' + 1;
            else
                u = tmp[0] - 'A' + 27;
            if(tmp[1] >= 'a' && tmp[1] <= 'z')
                v = tmp[1] - 'a' + 1;
            else
                v = tmp[1] - 'A' + 27;
            if(u >= 27 && u <= 39)
                AA = 1;
            if(u >= 40 && u <= 52)
                BB = 1;
            if(v >= 27 && v <= 39)
                AA = 1;
            if(v >= 40 && v <= 52)
                BB = 1;

            meow[u] = meow[v] = 1;

            if(u <= 26 && v <=26){
                adj[u][v] = 1;
                adj[v][u] = 1;
            }
            else{
                adj[u][v] = 1000;
                adj[v][u] = 1000;
            }
        }
        int cnt = 0;
        for (int i = 0; i < 54; i++)
            if (meow[i] == 0) cnt++;
        memset(meow, 0, sizeof(meow)); 
        Dsu dsu;
        dsu.init(54);
        for(int i = 1; i < 53; i++)
            for(int j = i + 1; j < 53; j++)
                if(adj[i][j] > 0 || adj[j][i] > 0)
                    dsu.merge(i, j);
        for(int i = 1; i < 53; i++)
            if(dsu.find(i) >= 27)
                meow[i] = 1;
        
        for(int i = 1; i <= 13; i++){
            if (meow[i + 26])
                adj[0][i + 26] = 1000;
            if (meow[i + 26 + 13])
                adj[i + 26 + 13][53] = 1000;
        }
        int ans = 87878787;
        for(int i = 1; i <= 26; i++) {
            if (!meow[i])
                continue;
            for(int j = 1; j <= 26; j++){
                if (!meow[j])
                    continue;
                if(i == j)
                    continue;
                dinic.init(54, 0, 53);
                dinic.add_edge(0, i, 87878787);
                dinic.add_edge(j, 53, 87878787);
                for(int x = 0; x < 54; x++)
                    for(int y = 0; y < 54; y++)
                        dinic.add_edge(x, y, adj[x][y]);
                ans = min(ans, dinic.flow());
            }
        }
        if(ans >= 87878787)
            printf("Case %d: impossible\n", ++t);
        else{
            if(AA == 0 && BB == 0)
                printf("Case %d: 0 0\n", ++t);
            else if(AA == 0 || BB == 0)
                printf("Case %d: %d %d\n", ++t, 0, dsu.cc - 1 - cnt);
            else
                printf("Case %d: %d %d\n", ++t, 2 * (ans / 1000), 2 * (ans % 1000) + dsu.cc - 2 - cnt);
        }
    }
    return 0;
}
