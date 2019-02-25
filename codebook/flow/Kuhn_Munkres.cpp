int nl , nr;
int mat_x[MAX_N] , mat_y[MAX_N];
bool vis_x[MAX_N] , vis_y[MAX_N];
ll slack_y[MAX_N], W[MAX_N][MAX_N], l_x[MAX_N] , l_y[MAX_N];
bool dfs(int x) {
    vis_x[x] = 1;
    REP1(y , 1 , nr) {
        if(vis_y[y]) continue;
        ll t = l_x[x] + l_y[y] - W[x][y];
        if(!t) {
            vis_y[y] = 1;
            if(!mat_y[y] || dfs(mat_y[y])) {
                mat_x[x] = y;
                mat_y[y] = x;
                return 1;
            }
        }
        else slack_y[y] = min(slack_y[y] , t);
    }
    return 0;
}
inline void modify() {
    ll t = INF64;
    REP1(y , 1 , nr) if(!vis_y[y]) t = min(t , slack_y[y]);
    REP1(x , 1 , nl) if(vis_x[x]) l_x[x] -= t;
    REP1(y , 1 , nr) if(vis_y[y]) l_y[y] += t;
}
int main() {
    int m;
    RI(nl , nr , m);
    nr = max(nl , nr);
    while(m--) {
        int x , y;
        ll w;
        RI(x , y , w);
        W[x][y] = w;
        l_x[x] = max(l_x[x] , w);
    }
    REP1(i , 1 , nl) {
        while(1) {
            REP1(x , 1 , nl) vis_x[x] = 0;
            REP1(y , 1 , nr) vis_y[y] = 0 , slack_y[y] = INF64;
            if(dfs(i)) break;
            else modify();
        }
    }
    ll ans = 0LL;
    REP1(x , 1 , nl) ans += W[x][mat_x[x]];
    PL(ans);
    REP1(x , 1 , nl) printf("%d%c",W[x][mat_x[x]] ? mat_x[x] : 0," \n"[x == nl]);
    return 0;
}
