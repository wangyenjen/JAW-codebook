#include <cstdio>
#include <tuple>
using namespace std;

struct Func {
    int x[10];

    Func(): x{0, 1, 2, 3, 4, 5, 6, 7, 8, 9} {}

    int operator() (int i) const { return x[i]; }
    Func &operator *= (Func rhs);
};

Func operator * (Func lhs, Func rhs) {
    Func out;
    for (int i = 0; i < 10; i++)
        out.x[i] = rhs(lhs(i));
    return out;
}
Func &Func::operator *= (Func rhs) {
    return *this = *this * rhs;
}

template<typename T>
T pow(T a, long long x) {
    if (x == 1)
        return a;
    T b = pow(a, x >> 1);
    b = b * b;
    if (x & 1)
        b = b * a;
    return b;
}

int solve(const Func (&f)[10], long long a, long long b, int n) {
    long long pow10 = n ? pow(10LL, n) : 1;

    Func prod;
    for (long long i = a + 1; i <= b;) {
        if (n < 18 && i % (pow10 * 10) == 0) {
            long long inc = (b + 1) / (pow10 * 10) - i / (pow10 * 10);
            if (inc) {
                Func ff;
                for (int j = 0; j < 10; j++)
                    ff *= pow(f[j], pow10);
                prod *= pow(ff, inc);

                i += inc * pow10 * 10;
                continue;
            }
        }

        long long inc = min((i / pow10 + 1) * pow10, b + 1) - i;

        // i / pow10 % 10
        prod *= pow(f[i / pow10 % 10], inc);
        i += inc;
    }
    

    return prod(a / pow10 % 10);
}

int main() {
#ifndef LOCAL
    freopen("binary.in", "r", stdin);
    freopen("binary.out", "w", stdout);
#endif

    Func f[10];

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            scanf("%d", f[j].x + i);

    long long a, b;
    scanf("%lld%lld", &a, &b);

    bool first = true;
    for (int i = 18; i >= 0; i--) {
        int ans = solve(f, a, b, i);
        if (ans || !first) {
            first = false;
            putchar('0' + ans);
        }
    }
    if (first)
        putchar('0');
    putchar('\n');
}
