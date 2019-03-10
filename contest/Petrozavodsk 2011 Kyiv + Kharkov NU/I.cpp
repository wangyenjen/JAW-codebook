#include <cstdio>
#include <algorithm>
using namespace std;

struct P {
    int x, y;
    void read() {
        scanf("%d%d", &x, &y);
    }
} p[100001];

long long cross(P a, P b) {
    return (long long) a.x * b.y - (long long) a.y * b.x;
}

long long gcd(long long a, long long b) {
    return __gcd(abs(a), abs(b));
}

unsigned long long solve(int n) {
    __float128 area = 0;
    long long edge = 0;

    p[n] = p[0];
    for (int i = 0; i + 1 <= n; i++) {
        area += cross(p[i], p[i + 1]);
        edge += gcd((long long) p[i].x - p[i + 1].x, (long long) p[i].y - p[i + 1].y);
    }

    // fprintf(stderr, "area=%lld edge=%lld solve=%lld\n", area, edge, (abs(area) + edge) / 2 + 1);

    return ((area < 0 ? -area : area) + edge) / 2 + 1;
}

int main() {
    freopen("semi-cool.in", "r", stdin);
    freopen("semi-cool.out", "w", stdout);
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        p[i].read();

    unsigned long long ans = solve(n);

    for (int i = 0; i < n; i++)
        p[i].x *= 2;
    ans -= solve(n);
    
    for (int i = 0; i < n; i++)
        p[i].y *= 2;
    ans += solve(n);

    for (int i = 0; i < n; i++)
        p[i].x /= 2;
    ans -= solve(n);

    printf("%lld\n", ans);
}
