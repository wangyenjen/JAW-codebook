#include <cstdio>
using namespace std;

constexpr int mod = 1'000'000'007;

struct Frac {
    long long a, b;
};
bool operator < (Frac l, Frac r) {
    return (__float128) l.a * r.b < (__float128) r.a * l.b;
}
Frac f(int x, int m) {
    return Frac { (long long) (x + 1 + m) * (m - x) - (long long) x * (1 + x),
                  4LL * (m - x) };
}

int pow(int a, int n) {
    if (n == 0)
        return 1;
    int x = pow(a, n >> 1);
    x = (long long) x * x % mod;
    if (n & 1)
        x = (long long) x * a % mod;
    return x;
}

int solve(int m) {
#if 1
    int l = 0, r = m - 1;
    while (l < r) {
        int x = (l + r) >> 1;
        if (f(x + 1, m) < f(x, m))
            r = x;
        else
            l = x + 1;
    }

    Frac ans = f(l, m);
#else
    Frac ans = f(0, m);
    for (int x = 1; x < m; x++) {
        Frac y = f(x, m);
        if (y < ans)
            break;
        ans = y;
    }
#endif
    
    return ans.a % mod * pow(ans.b % mod, mod - 2) % mod;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int m;
        scanf("%d", &m);
        printf("%d\n", solve(m));
    }
}
