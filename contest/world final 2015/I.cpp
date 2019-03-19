#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
int main() {
    int n, w, u, v, t1_, t2;
    scanf("%d%d%d%d%d%d", &n, &w, &u, &v, &t1_, &t2);

    vector<pair<double, double>> ban;

    for (int i = 0; i < n; i++) {
        char dir;
        int m;
        scanf(" %c%d", &dir, &m);

        for (int j = 0; j < m; j++) {
            int l, p;
            scanf("%d%d", &l, &p);
            if (dir == 'E')
                p = -p;
            ban.emplace_back((double) p / u - (double) (w * (i + 1)) / v,
                             (double) (p + l) / u - (double) w * i / v);
        }
    }

    sort(ban.begin(), ban.end());
#if 0
    for (auto [l, r] : ban)
        fprintf(stderr, "BAN %.10f %.10f\n", l, r);
#endif

    double t1 = t1_, ans = 0;
    for (auto [l, r] : ban) {
        if (t1 >= t2)
            break;
        if (t1 < l)
            ans = max(ans, min(l, (double) t2) - t1);
        t1 = max(t1, r);
    }
    if (t1 < t2)
        ans = max(ans, t2 - t1);

    printf("%.10f\n", ans);
}
