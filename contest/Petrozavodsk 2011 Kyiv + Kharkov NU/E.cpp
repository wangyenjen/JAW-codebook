#include <bits/stdc++.h>

using namespace std;

const int N = 300010;
struct SA {
#define REP(i, n) for (int i = 0; i < int(n); i++)
#define REP1(i, a, b) for (int i = (a); i <= int(b); i++)
    bool _t[N << 1];
    int _s[N << 1], _sa[N << 1], _c[N << 1], x[N], _p[N], _q[N << 1], hei[N], r[N];

    int operator [] (int i) {
        return _sa[i];
    }

    void build(char *s, int n, int m) {
        copy_n(s, n, _s);
        sais(_s, _sa, _p, _q, _t, _c, n, m);
        mkhei(n);
    }

    void mkhei(int n) {
        REP(i, n)
            r[_sa[i]] = i;
        hei[0] = 0;
        REP(i, n)
            if (r[i]) {
                int ans = i > 0 ? max(hei[r[i - 1]] - 1, 0) : 0;
                while (_s[i + ans] == _s[_sa[r[i] - 1] + ans])
                    ans++;
                hei[r[i]] = ans;
            }
    }

    void sais(int *s, int *sa, int *p, int *q, bool *t, int *c, int n, int z) {
        bool uniq = t[n - 1] = true, neq;
        int nn = 0, nmxz = -1, *nsa = sa + n, *ns = s + n, lst = -1;
#define MS0(x, n) memset((x), 0, n * sizeof(*(x)))
#define MAGIC(XD) MS0(sa, n); \
        memcpy(x, c, sizeof(int) * z); \
        XD; \
        memcpy(x + 1, c, sizeof(int) * (z - 1)); \
        REP(i,n) if(sa[i] && !t[sa[i]-1]) sa[x[s[sa[i]-1]]++] = sa[i]-1; \
        memcpy(x, c, sizeof(int) * z); \
        for(int i = n - 1; i >= 0; i--) if(sa[i] && t[sa[i]-1]) sa[--x[s[sa[i]-1]]] = sa[i]-1;
        MS0(c, z);
        REP(i,n) uniq &= ++c[s[i]] < 2;
        REP(i,z-1) c[i+1] += c[i];
        if (uniq) { REP(i,n) sa[--c[s[i]]] = i; return; }
        for(int i = n - 2; i >= 0; i--) t[i] = (s[i]==s[i+1] ? t[i+1] : s[i]<s[i+1]);
        MAGIC(REP1(i,1,n-1) if(t[i] && !t[i-1]) sa[--x[s[i]]]=p[q[i]=nn++]=i);
        REP(i, n) if (sa[i] && t[sa[i]] && !t[sa[i]-1]) {
          neq=lst<0||memcmp(s+sa[i],s+lst,(p[q[sa[i]]+1]-sa[i])*sizeof(int));
          ns[q[lst=sa[i]]]=nmxz+=neq;
        }
        sais(ns, nsa, p + nn, q + n, t + n, c + z, nn, nmxz + 1);
        MAGIC(for(int i = nn - 1; i >= 0; i--) sa[--x[s[p[nsa[i]]]]] = p[nsa[i]]);
    }
} sa;

int H[N], SA[N], R[N];

void suffix_array(char *ip, int len) {
    ip[len++] = 0;
    sa.build(ip, len, 128);
    for (int i = 0; i < len - 1; i++) {
        H[i] = sa.hei[i + 1];
        SA[i] = sa._sa[i + 1];
        R[SA[i]] = i;
    }
}

char s[200002];
int dp[18][200001];

void build_table(int n) {
    copy_n(H, n, dp[0]);

    for (int i = 0; i + 1 < 18; i++)
        for (int j = 0; j + (2 << i) <= n; j++)
            dp[i + 1][j] = min(dp[i][j], dp[i][j + (1 << i)]);
}

int query(int l, int r) {
    int x = __lg(r - l);
    return min(dp[x][l], dp[x][r - (1 << x)]);
}

int go(int n, int l, int r) {
    if (l < 0 || r >= n)
        return 0;

    pair<int, int> pa = minmax(R[2 * n - l], R[r]);
    return query(pa.first + 1, pa.second + 1);
}

int main() {
    freopen("palindromes.in", "r", stdin);
    freopen("palindromes.out", "w", stdout);

    scanf("%100000s", s);
    int n = strlen(s);

    s[n] = '$';
    reverse_copy(s, s + n, s + n + 1);
    for (int i = n + 1; i < 2 * n + 1; i++)
        if (s[i] == '?')
            s[i] = '!';
    s[2 * n + 1] = '\0';

    suffix_array(s, 2 * n + 1);
    build_table(2 * n + 1);

    double ans = 0;
    for (int center = 0; center < n; center++) {
        double p = 1.0;
        for (int nq = 0, l = center, r = center; nq < 20; nq++, p /= 26) {
            if (l < 0 || r >= n || (s[l] != s[r] && s[l] != '?' && s[r] != '?'))
                break;
            int x = 1 + go(n, l - 1, r + 1);
            ans += x * p;
            l -= x;
            r += x;
        }
    }

    printf("%.9f\n", ans * 2 / n - 1);
}
