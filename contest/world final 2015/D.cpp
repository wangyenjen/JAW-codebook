#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 10000 + 7;
const double PI = acos(-1);

int n;
int X[MAX_N], Y[MAX_N], Z[MAX_N], R[MAX_N];

double calc(double z) {
    double res = z * 1e10;
    for (int i = 0; i < n; i++) {
        double d = z - Z[i];
        if (d <= -R[i]) 
            continue;
        if (d >= R[i]) {
            res -= 4.0 / 3.0 * PI * R[i] * R[i] * R[i];
            continue;
        }
        double t = 0.0;
        t = 2.0 / 3.0 * PI * R[i] * R[i] * R[i];
        t += (1. * R[i] * R[i] * d - 1. / 3. * d * d * d) * PI;
        res -= t;
    }
    return res;
}

int main() {
    int s;
    scanf("%d%d", &n, &s);
    double nd = 1e15;
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d%d", &R[i], &X[i], &Y[i], &Z[i]);
        nd -= 4.0 / 3.0 * PI * R[i] * R[i] * R[i];
    }
    nd /= s;
    vector<double> ans;
    double pre = 0.0, sum = 0.0;
    for (int i = 0; i < s; i++) {
        sum += nd;
        double lb = pre, rb = 1e5;
        for (int times = 0; times < 50; times++) {
            double mid = (lb + rb) / 2.0;
            if (calc(mid) < sum)
                lb = mid;
            else
                rb = mid;
        }
        double z = (lb + rb) / 2.0;
        ans.push_back(z - pre);
        pre = z;
    }
    for (int i = 0; i < s; i++)
        printf("%.10f\n", ans[i] / 1000.0);
    return 0;
}
