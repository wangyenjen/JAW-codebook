#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;

constexpr int mod = 1000000007;

struct P {
    int x, y;
    void read() {
        scanf("%d%d", &x, &y);
    }
} p[2002];

bool test(int xl, int xr, int yl, int yr, int n) {
    return all_of(p + 1, p + n + 1,
            [=](P pp) {
                return pp.x < xl || pp.x > xr || pp.y < yl || pp.y > yr;
            });
}

int main() {
    freopen("rectangles.in", "r", stdin);
    freopen("rectangles.out", "w", stdout);

    int w, h, n;
    scanf("%d%d%d", &w, &h, &n);
    p[0] = {-1, -1};
    for (int i = 1; i <= n; i++)
        p[i].read();
    p[n + 1] = {w + 1, h + 1};

    sort(p + 1, p + n + 1,
            [](P l, P r) {
                return l.x < r.x;
            });

    int cnt = 0;

#if 0
    for (int xl = 0; xl <= w; xl++)
        for (int xr = xl; xr <= w; xr++)
            for (int yl = 0; yl <= h; yl++)
                for (int yr = yl; yr <= h; yr++)
                    if (test(xl, xr, yl, yr, n))
                        cnt++;
#else
    for (int l = 0; l <= n; l++) {
        set<int> ys;
        ys.insert(p[0].y);
        ys.insert(p[n + 1].y);
        long long ycnt = (long long) (p[n + 1].y - p[0].y) * (p[n + 1].y - p[0].y - 1) / 2;

        for (int r = l; r <= n; r++) {
            int xll = p[l].x + 1, xlr = p[l + 1].x + 1;
            int xrl = p[r].x, xrr = p[r + 1].x;

            xrl = max(xrl, xll);
            xlr = min(xlr, xrr);

            long long xcnt = (long long) (xlr - xll) * (xrr - xrl);
            if (xlr > xrl)
                xcnt -= (long long) (xlr - xrl) * (xlr - xrl - 1) / 2;
            xcnt %= mod;

            if (xll >= xlr || xrl >= xrr)
                xcnt = 0;

            // fprintf(stderr, "xll=%d xlr=%d xrl=%d xrr=%d xcnt=%lld\n", xll, xlr, xrl, xrr, xcnt);

            cnt = (cnt + xcnt * (ycnt % mod)) % mod;

            auto pa = ys.insert(p[r + 1].y);
            if (pa.second) {
                int y0 = *prev(pa.first);
                int y1 = *pa.first;
                int y2 = *next(pa.first);

                ycnt -= (long long) (y2 - y0) * (y2 - y0 - 1) / 2;
                ycnt += (long long) (y2 - y1) * (y2 - y1 - 1) / 2;
                ycnt += (long long) (y1 - y0) * (y1 - y0 - 1) / 2;
            }
        }
    }
#endif

    printf("%d\n", cnt % mod);
}
