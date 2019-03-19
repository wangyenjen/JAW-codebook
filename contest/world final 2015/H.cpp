#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1000 + 7;

double a[MAX_N], x[MAX_N];

double sqr(double t) {
    return t * t;
}

int main() {
    int w, h, n;
    scanf("%d%d%d", &w, &h, &n);
    double lambda = 1. * h / w;
    a[0] = 0;
    a[1] = 1;
    for (int i = 2; i <= n + 1; i++) 
        a[i] = 2 / (1 - sqr(lambda)) * a[i - 1] - a[i - 2];
    x[0] = 0;
    for (int i = 1; i <= n + 1; i++)
        x[i] = a[i] / a[n + 1] * w;
    double ans = 0.5 * lambda * sqr(w);
    for (int i = 1; i <= n + 1; i++)
        ans += 0.5 * sqr(x[i] * lambda) + 0.25 * sqr(x[i] - x[i - 1]) * (1 - sqr(lambda));
    printf("%.10f\n", ans);
    for (int i = 1; i <= min(n, 10); i++)
        printf("%.10f\n", x[i]);
    return 0;
}
