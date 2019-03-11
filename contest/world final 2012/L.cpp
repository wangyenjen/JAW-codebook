#include <cstdio>
#include <algorithm>
#include <functional>
using namespace std;

bool solve2(long long *a, long long *ae, long long *b, long long *be) {
    if (a == ae)
        return false;
    if (b == be)
        return true;

    long long sa = *a++, sb = *b++;

    for (int i = 0; ; i++) {
        if (i && sa > sb)
            return true;
        if (a != ae)
            sa += *a++;

        if (sb > sa)
            return false;
        if (b != be)
            sb += *b++;
    }
}

long long a[100000];
long long b[100000];

bool solve(int n, int m) {
    sort(a, a + n, greater<long long>());
    sort(b, b + m, greater<long long>());

    if (solve2(a, a + n, b, b + m))
        return true;
    if (a[0] > b[0] && !solve2(b + 1, b + m, a, a + n))
        return true;
    return false;
}

int main() {
    for (int t = 1, n, m; scanf("%d%d", &n, &m) == 2; t++) {
        for (int i = 0; i < n; i++)
            scanf("%lld", a + i);
        for (int i = 0; i < m; i++)
            scanf("%lld", b + i);
        printf("Case %d: %s\n", t, solve(n, m) ? "Takeover Incorporated" : "Buyout Limited");
    }
}
