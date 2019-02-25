#include <cstdio>
#include <iterator>
#include <algorithm>
#include <map>
using namespace std;
struct M {
    int d, p, r, g;
    void read() {
        scanf("%d%d%d%d", &d, &p, &r, &g);
        d--;
    }
    bool operator < (M rhs) const {
        return d < rhs.d;
    }
} m[100001];

bool check(pair<int, long long> l1,
           pair<int, long long> l2,
           pair<int, long long> l3) {
    int a1 = l1.first, a2 = l2.first, a3 = l3.first;
    long long b1 = l1.second, b2 = l2.second, b3 = l3.second;
    return (__float128) (b1 - b2) * (a3 - a2) <
           (__float128) (b2 - b3) * (a2 - a1);
}

long long dp[100001];
long long solve(int n, int c, int d) {
    for (int i = 0; i < n; i++)
        m[i].read();

    sort(m, m + n);
    m[n].p = 0;
    m[n].d = d;

    map<int, long long> mp;
    for (int i = 0; i <= n; i++) {
        long long prebuy = c;
#if 0
        for (int j = 0; j < i; j++)
            if (dp[j] >= 0)
                prebuy = max(prebuy, dp[j] + (long long) (m[i].d - m[j].d - 1) * m[j].g + m[j].r);
#elif 0
        for (auto p : mp) {
            int aj = p.first;
            long long bj = p.second;

            prebuy = max(prebuy, (long long) aj * m[i].d + bj);
        }
#else
        if (!mp.empty()) {
            auto it = mp.begin();
            long long x = (long long) it->first * m[i].d + it->second;
            while (++it != mp.end()) {
                long long y = (long long) it->first * m[i].d + it->second;
                if (x <= y) {
                    x = y;
                    mp.erase(prev(it));
                } else {
                    break;
                }
            }
            prebuy = max(prebuy, x);
        }
#endif
        dp[i] = prebuy - m[i].p;

        if (i < n && dp[i] >= 0) {
            int ai = m[i].g;
            long long bi = dp[i] - (long long) (m[i].d + 1) * m[i].g + m[i].r;

            auto it = mp.emplace(ai, bi).first;
            it->second = max(it->second, bi);

            if (it != mp.begin() && next(it) != mp.end() && !check(*prev(it), *it, *next(it))) {
                mp.erase(it);
            } else {
                while (it != mp.begin() && prev(it) != mp.begin() && !check(*prev(it, 2), *prev(it), *it))
                    mp.erase(prev(it));
                while (next(it) != mp.end() && next(it, 2) != mp.end() && !check(*it, *next(it), *next(it, 2)))
                    mp.erase(next(it));
            }
        }
    }

    return dp[n];
}
int main() {
    for (int t = 1, n, c, d; scanf("%d%d%d", &n, &c, &d), n; t++)
        printf("Case %d: %lld\n", t, solve(n, c, d));
}
