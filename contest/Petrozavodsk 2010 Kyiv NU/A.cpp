#include <cstdio>
#include <cmath>
using namespace std;

struct I {
    int a, n, x; // a * x**n

    I(int _a, int _x): a(_a), n(0), x(_x) {
        while (a % x == 0)
            a /= x, n++;
    }

    I &operator *= (int rhs) {
        while (rhs % x == 0)
            rhs /= x, n++;
        a = (long long) a * rhs % x;
        return *this;
    }
};

double solve(int n, int s) {
    // TODO reduce time complexity
    // TODO improve accuracy
    double sum = 0;
    for (int i = 2; i < n; i++) {
        double prod = s;
        for (int j = n - i; j <= n - 1; j++)
            prod *= j;
        for (int j = 1; j <= i; j++)
            prod /= j;
        prod /= i;

        sum += prod - floor(prod);
    }
    return sum - floor(sum);
}

int main() {
    // freopen("average.in", "r", stdin);
    // freopen("average.out", "w", stdout);
#if 1
    for (int n = 2; n <= 20; n++)
        printf("n=%d ans=%.10g\n", n, solve(n, 1));
#else
    int n, s;
    scanf("%d%d%*d", &n, &s);
    printf("%.10f\n", solve(n, s));
#endif
}
