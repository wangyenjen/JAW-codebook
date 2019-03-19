#include <cstdio>
#include <cassert>
#include <algorithm>
using namespace std;

bool check(int a, int p, int b, int q) {
    return (p - q > 30) || ((a >> (p - q)) < b);
}
void minus(int &a, int &p, int b, int q) {
    a = (a << (q - p)) - b;
    p = q;
}

int solve(int ls, int v1, int v2, int t) {
    if (v2 - v1 <= t)
        return 0;

    int r = (v2 - v1 - 1) / t;

    int a = 1, b = 0;
    for (int j = 1; v2 - j * t > v1;) {
        int i = ls / (v2 - j * t);

#if 0
        int c = 1;
        while (v2 - (j + c) * t > v1 && ls / (v2 - (j + c) * t) == i)
           c += 1;
#else
        int c = min(r, (v2 - ls / (i + 1) - 1) / t - j + 1);
#endif
        // fprintf(stderr, "c=%d i=%d\n", c, i);

        if (check(r, i, a, b)) {
            for (int i2 = b; i2 < i; i2++)
                if (check(r, i2, a, b))
                    return i2;
            return i;
        }
        if (!check(c, i, a, b))
            return -1;
        minus(a, b, c, i);

        j += c;
        r -= c;
    }

    assert(false);
}

int main() {
    int c;
    scanf("%d", &c);
    while (c--) {
        int l, v1, v2, t, s;
        scanf("%d%d%d%d%d", &l, &v1, &v2, &t, &s);
        int ans = solve(l / s, v1, v2, t);
        if (ans >= 0)
            printf("%d\n", ans);
        else
            puts("impossible");
    }
}
