#pragma GCC optimize "-O3"
#include <cstdio>
#include <cassert>
#include <algorithm>
#include <iterator>
using namespace std;

namespace {

constexpr int dr[] = {1, 0, -1, 0};
constexpr int dc[] = {0, 1, 0, -1};

int mod1(int r, int n) {
    return r >= n ? r - n : r;
}

struct P {
    int r, c, p, q;

    P (): r(0), c(0), p(0), q(0) {}

    P (int _r, int _c, int _p, int _q): r(_r), c(_c), p(_p), q(_q) {}

    P (int x): r(x % 2048u), c((x >> 11) % 2048u), p((x >> 22) & 3), q(x >> 24) {}

    operator int () const {
        return r + (c << 11) + (p << 22) + (q << 24);
    }

    void operator () (int n, P (&a)[6]) const {
        // H
        a[0] = P(r, mod1(c + 1, n), p, q);
        // R
        a[1] = P(c, n - 1 - r, (p + 3) & 3, (q + 3) & 3);
        // T
        a[2] = P(c, r, p ^ 1, q ^ 1);
        // V
        a[3] = P(mod1(r + 1, n), c, p, q);
        // X
        a[4] = P(r, n - 1 - c, p ^ ((p & 1) << 1), q ^ ((q & 1) << 1));
        // Y
        a[5] = P(n - 1 - r, c, p ^ ((~p & 1) << 1), q ^ ((~q & 1) << 1));
    }
    void operator () (int n, P (&a)[6], int) const {
        // H'
        a[0] = P(r, mod1(c + n - 1, n), p, q);
        // R'
        a[1] = P(n - 1 - c, r, (p + 1) & 3, (q + 1) & 3);
        // T' = T
        a[2] = P(c, r, p ^ 1, q ^ 1);
        // V'
        a[3] = P(mod1(r + n - 1, n), c, p, q);
        // X' = X
        a[4] = P(r, n - 1 - c, p ^ ((p & 1) << 1), q ^ ((q & 1) << 1));
        // Y' = Y
        a[5] = P(n - 1 - r, c, p ^ ((~p & 1) << 1), q ^ ((~q & 1) << 1));
    }
};

int dir_of(int n, int r1, int c1, int r2, int c2) {
    int ddr = r2 - r1, ddc = c2 - c1;
    for (int i = 0; i < 4; i++)
        if ((dr[i] - ddr) % n == 0 && (dc[i] - ddc) % n == 0)
            return i;
    assert(false);
}

P read_p(int n) {
    int r1 = -1, c1 = -1;
    int r2 = -1, c2 = -1;
    int rn = -1, cn = -1;
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++) {
            int x;
            scanf("%d", &x);
            if (x == 1)
                r1 = r, c1 = c;
            else if (x == 2)
                r2 = r, c2 = c;
            else if (x == n + 1)
                rn = r, cn = c;
        }

    assert(r1 >= 0);
    assert(r2 >= 0);
    assert(rn >= 0);

    return P{r1, c1, dir_of(n, r1, c1, r2, c2), dir_of(n, r1, c1, rn, cn)};
}

constexpr int inf = 30000;
short dist[2000 * 2000 * 4 * 4];
int que[2000 * 2000 * 4 * 2];

}

int main() {
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout);

    int n;
    scanf("%d", &n);

    if (n == 1)
        return 0;

    fill(begin(dist), end(dist), inf);

    P src = {0, 0, 1, 0};
    P dest = read_p(n);

    int qb = 0, qe = 0;
    que[qe++] = src;
    dist[src] = 0;
    if (n == 2) {
        que[qe++] = P(src.r, src.c, src.p, src.q ^ 2);
        dist[que[qe - 1]] = 0;
        que[qe++] = P(src.r, src.c, src.p ^ 2, src.q);
        dist[que[qe - 1]] = 0;
        que[qe++] = P(src.r, src.c, src.p ^ 2, src.q ^ 2);
        dist[que[qe - 1]] = 0;
    }

    while (qb != qe) {
        P p = que[qb++];
        int d = dist[p] + 1;

        P nei[6];
        p(n, nei, 0);

        for (P q : nei)
            if (dist[q] > d)
                dist[q] = d, que[qe++] = q;
    }

    int d = dist[dest];
    for (int i = d - 1; i >= 0; i--) {
        P nei[6];
        dest(n, nei);

        for (int j = 0; j < 6; j++)
            if (dist[nei[j]] == i) {
                putchar("HRTVXY"[j]);
                // printf("%d ", j);
                dest = nei[j];
                break;
            }
    }

    putchar('\n');
}
