#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

constexpr long double pi = acos(-1);
long double d[50000], t[50000];

bool check(long double r, int n, int k) {
    long double c = 2 * pi / k;
    long double r2 = r * cos(pi / k);

    vector<pair<long double, long double>> v;
    for (int i = 0; i < n; i++) {
        if (d[i] <= r2)
            continue;
        long double th = acos(r2 / d[i]);
        long double a = t[i] - th;
        // long double b = t[i] + th;

        a = fmod(a, c);
        if (a < 0)
            a += c;
        long double b = a + 2 * th;

        // fprintf(stderr, "r2=%f d=%f t=%f allowed: [%f, %f] mod %f\n", r2, d[i], t[i], a, b, c);

        if (b < c) {
            v.emplace_back(a, b);
            // v.emplace_back(0, a);
            // v.emplace_back(b, c);
        } else {
            v.emplace_back(0, b - c);
            v.emplace_back(a, c);
            // v.emplace_back(b - c, a);
        }
    }

    sort(v.begin(), v.end());
    long double rb = 0;
    for (auto [a, b] : v) {
        if (a > rb)
            return true;
        rb = max(rb, b);
    }
    return rb < c;
}

int main() {
    freopen("tower.in", "r", stdin);
    freopen("tower.out", "w", stdout);
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        d[i] = hypot(y, x);
        t[i] = atan2(y, x);
    }

    long double l = *max_element(d, d + n);
    long double r = l * 2;

    for (int i = 0; i < 100; i++) {
        long double m = (l + r) / 2;
        (check(m, n, k) ? r : l) = m;
    }
    printf("%.15Lf\n", r);
}
