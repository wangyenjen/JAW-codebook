#include <bits/stdc++.h>

using namespace std;

const double INF = 1e30;

double p, a, b, c, d;

double price(double k) {
    return p * (sin(a * k + b) + cos(c * k + d) + 2);
}

int main() {
    scanf("%lf%lf%lf%lf%lf", &p, &a, &b, &c, &d);
    int n;
    scanf("%d", &n);
    double mx = -INF, ans = 0.0;
    for (int i = 1; i <= n; i++) {
        double x = price(i);
        if (i > 1)
            ans = max(ans, mx - x);
        mx = max(mx, x);
    }
    printf("%.10f\n", ans);
    return 0;
}
