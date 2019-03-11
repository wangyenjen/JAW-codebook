#include <bits/stdc++.h>

using namespace std;

const double PI = acos(-1.0);

double calc(vector<double> vs, double l, double r) {
    double res = 0.0;
    for (int i = 0; i < (int)vs.size(); i++) {
        res += PI * (pow(r, (i + 1)) - pow(l, (i + 1))) / (i + 1) * vs[i];
    }
    return res;
}

int main() {
    int kcase = 0, n;
    while (scanf("%d", &n) != EOF) {
        vector<double> vs;
        for (int i = 0; i <= n; i++) {
            double x;
            scanf("%lf", &x);
            vs.push_back(x);
        }
        vector<double> vs2;
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                if (i + j >= (int)vs2.size())
                    vs2.push_back(0.0);
                vs2[i + j] += vs[i] * vs[j];
            }
        }
        vs = vs2;
        double xl, xr;
        scanf("%lf%lf", &xl, &xr);
        double inc;
        scanf("%lf", &inc);
        double ori = calc(vs, xl, xr);
        printf("Case %d: %.2f\n", ++kcase, ori);
        if (ori < inc) {
            puts("insufficient volume");
            continue;
        }
        vector<double> ans;
        for (int i = 1; i <= 8 && i * inc <= ori; i++) {
            double lb = xl, rb = xr;
            for (int times = 0; times < 50; times++) {
                double mid = (lb + rb) / 2;
                if (calc(vs, xl, mid) < i * inc)
                    lb = mid;
                else
                    rb = mid;
            }
            ans.push_back(lb);
        }
        for (int i = 0; i < (int)ans.size(); i++)
            printf("%.2f%c", ans[i] - xl, " \n"[i == (int)ans.size() - 1]);
    }
    return 0;
}
