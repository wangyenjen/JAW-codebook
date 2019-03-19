#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
#include <cassert>
using namespace std;

constexpr long long inf = 1'000'000'000'000'000;

int a[100000], b[100000], t[100000];
int es[200000];

long long sum[(1 << 18) * 2 - 1];
pair<long long, int> mx[(1 << 18) * 2 - 1];

void seg_init(int nl = 0, int nr = 1 << 18, int k = 0) {
    if (nl + 1 == nr) {
        sum[k] = 0;
        mx[k] = {0, nl};
    } else {
        int nm = (nl + nr) >> 1;
        seg_init(nl, nm, 2 * k + 1);
        seg_init(nm, nr, 2 * k + 2);

        sum[k] = 0;
        mx[k] = min(mx[2 * k + 1], mx[2 * k + 2]);
    }
}
void seg_add(int l, int r, int x,
             int nl = 0, int nr = 1 << 18, int k = 0) {
    if (l <= nl && nr <= r) {
        sum[k] += x;
        mx[k].first += x;
    } else if (!(r <= nl || nr <= l)) {
        int nm = (nl + nr) >> 1;
        seg_add(l, r, x, nl, nm, 2 * k + 1);
        seg_add(l, r, x, nm, nr, 2 * k + 2);

        mx[k] = min(mx[2 * k + 1], mx[2 * k + 2]);
        mx[k].first += sum[k];
    }
}
pair<long long, int> seg_query(int l, int r,
                               int nl = 0, int nr = 1 << 18, int k = 0) {
    if (l <= nl && nr <= r) {
        return mx[k];
    } else if (r <= nl || nr <= l) {
        return make_pair(inf, 0);
    } else {
        int nm = (nl + nr) >> 1;
        auto ret = min(seg_query(l, r, nl, nm, 2 * k + 1),
                       seg_query(l, r, nm, nr, 2 * k + 2));
        ret.first += sum[k];
        return ret;
    }
}

int main() {
    freopen("lamps.in", "r", stdin);
    freopen("lamps.out", "w", stdout);

    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d%d%d", a + i, b + i, t + i);
    
    {
        vector<int> v;
        for (int i = 0; i < n; i++) {
            v.push_back(a[i]);
            v.push_back(b[i]);
        }
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());

        for (int i = 0; i < n; i++) {
            a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin();
            b[i] = lower_bound(v.begin(), v.end(), b[i]) - v.begin();
        }
    }

    iota(es, es + 2 * n, 0);
#define TIME_AT(I) (((I) & 1) ? b[(I) >> 1] : a[(I) >> 1])
    sort(es, es + 2 * n, [](int l, int r) {
        return TIME_AT(l) < TIME_AT(r);
    });

    multiset<int> rema, remb;
    seg_init();
    for (int i = 0; i < n; i++) {
        seg_add(a[i], b[i], t[i]);
        rema.insert(a[i]);
        remb.insert(b[i]);
    }

    long long bcost = inf;
    int bl = 0, br = 0;

    int lcnt = 0, rcnt = n;
    long long lcost = 0;
    for (int i = 0, l = 0; l < 2 * n; l++) {
        for (; i < 2 * n && TIME_AT(es[i]) <= l; i++) {
            bool end = es[i] & 1;
            int ei = es[i] >> 1;
            if (end) {
                lcnt++;
                lcost -= t[ei];
            } else {
                rcnt--;
                lcost += t[ei];
                seg_add(a[ei], b[ei], -t[ei]);
                rema.erase(rema.find(a[ei]));
                remb.erase(remb.find(b[ei]));
            }
        }

        if (lcnt == 0 || rcnt == 0)
            continue;

        int rl = *remb.begin(), rr = *--rema.end();

        if (rl >= rr)
            continue;

        auto [rcost, r] = seg_query(rl, rr);
        if (lcost + rcost < bcost) {
            bcost = lcost + rcost;
            bl = l;
            br = r;
        }
    }

    if (bcost == inf) {
        puts("-1");
        return 0;
    }

    printf("%lld\n", bcost);

    vector<int> ans;
    for (int i = 0; i < n; i++)
        if ((a[i] <= bl && bl < b[i]) || (a[i] <= br && br < b[i]))
            ans.push_back(i);
    printf("%zd\n", ans.size());

    sort(ans.begin(), ans.end());
    for (int i = 0; i < (int) ans.size(); i++)
        printf("%d%c", ans[i] + 1, i == (int) ans.size() - 1 ? '\n' : ' ');
}
