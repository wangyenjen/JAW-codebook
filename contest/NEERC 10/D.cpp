#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-10;
const int MAX_N = 10000 + 7;
const double PI = acos(-1.0);

int n;
double r[MAX_N], z[MAX_N];

double calc_r(double h) {
    double mx = 0;
    for (int i = 0; i < n; i++)
        mx = max(mx, r[i] * h / (h - z[i]));
    return mx;
}

double calc(double h) {
    double rr = calc_r(h);
    return PI * h / 3 * rr * rr;
}

int main() {
    freopen("dome.in", "r", stdin);
    freopen("dome.out", "w", stdout);
    scanf("%d", &n);
    double lb = 0, rb = 1e10;
    for (int i = 0; i < n; i++) {
        double x, y;
        scanf("%lf%lf%lf", &x, &y, &z[i]);
        r[i] = sqrt(x * x + y * y);
        lb = max(lb, z[i] + EPS);
    }
#if 0
    printf("%.10f %.10f\n", 1.1, calc(1.1));
    printf("%.10f %.10f\n", 1.9, calc(1.9));
    printf("%.10f %.10f\n", 2.0, calc(2));
    printf("%.10f %.10f\n", 2.1, calc(2.1));
    printf("%.10f %.10f\n", 2.9, calc(2.9));
    printf("%.10f %.10f\n", 3.0, calc(3));
    printf("%.10f %.10f\n", 3.1, calc(3.1));
    printf("%.10f %.10f\n", 4.0, calc(4));
#endif
    for (int times = 0; times < 100; times++) {
        double m1 = lb + (rb - lb) / 3.0;
        double m2 = rb - (rb - lb) / 3.0;
        if (calc(m1) < calc(m2))
            rb = m2;
        else
            lb = m1;
    }
    double h = (lb + rb) / 2.0;
    printf("%.3f %.3f\n", h, calc_r(h));
    return 0;
}
