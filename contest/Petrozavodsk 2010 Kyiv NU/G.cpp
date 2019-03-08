#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 100000 + 7;

struct Line {
    ll slope , inter;

    Line(ll _slope = 0 , ll _inter = 0) : slope(_slope) , inter(_inter) {}

    ll get_val(ll x) {
        return slope * x + inter;
    }

    bool operator < (const Line &rhs) const {
        if(slope != rhs.slope) return slope < rhs.slope;
        else return inter > rhs.inter;
    }
};

inline bool can_pop(const Line a, const Line b, const Line c) {
    return (a.inter - c.inter) * (b.slope - a.slope) <= (a.inter - b.inter) * (c.slope - a.slope);
}

ll dp[MAX_N];
ll X[MAX_N], C[MAX_N], T[MAX_N];

void cdq_dq(int l , int r) {
    if(l == r) {
        // if(l) dp[l] = max(dp[l] , dp[l - 1]);
        return;
    }
    int m = (l + r) >> 1;
    cdq_dq(l , m);
    vector<Line> ls , ls_tmp;
    for(int i = l; i <= m; i++) {
        ls.push_back(Line(C[i] , -C[i] * X[i] + dp[i]));
        ls.push_back(Line(-C[i] , C[i] * X[i] + dp[i]));
    }
    sort(ls.begin() , ls.end());
    for(Line l : ls) {
        if(!ls_tmp.empty() && ls_tmp.back().slope == l.slope) continue;
        ls_tmp.push_back(l);
    }
    ls = ls_tmp;
    ls_tmp.clear();
    for(Line l : ls) {
        while((int)ls_tmp.size() > 1 && can_pop(ls_tmp[(int)ls_tmp.size() - 2] , ls_tmp.back() , l)) ls_tmp.pop_back();
        ls_tmp.push_back(l);
    }
    vector<int> odr;
    for (int i = m + 1; i <= r; i++)
        odr.push_back(i);
    sort(odr.begin(), odr.end(), [&] (const int x, const int y) {
        return X[x] < X[y];    
    });
    int p = 0;
    ls = ls_tmp;
    for (int i : odr) {
        while(p + 1 < (int)ls.size() && ls[p].get_val(X[i]) <= ls[p + 1].get_val(X[i])) p++;
        if(p < (int)ls.size()) dp[i] = max(dp[i] , ls[p].get_val(X[i]) + T[i]);
    }
    cdq_dq(m + 1 , r);
}


int main() {
    freopen("travel.in", "r", stdin);
    freopen("travel.out", "w", stdout);
    int N;
    scanf("%d", &N);
    for (int i = 1; i <= N; i++)
        scanf("%lld%lld%lld", &X[i], &C[i], &T[i]);
    /*
    dp[1] = 0;
    for (int i = 2; i <= N; i++) {
        for (int j = 1; j < i; j++) {
            dp[i] = max(dp[i], dp[j] + abs(X[i] - X[j]) * C[j] + T[i]);
        } 
    }
    printf("%lld\n", dp[N]);
    */
    cdq_dq(1, N);
    printf("%lld\n", dp[N]);
    return 0;
}
