#include <bits/stdc++.h>

using namespace std;

int n;
double P[4];
priority_queue<double, vector<double>, greater<double> > pq;

void dfs(int t = 0, double p = 1.0) {
    if (t == n) {
        pq.push(p);
        return;
    }
    for (int i = 0; i < 4; i++) 
        dfs(t + 1, p * P[i]);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < 4; i++)
        scanf("%lf", &P[i]);
    if (n >= 10) {
        double res = 0.0;
        for (int i = 0; i < 4; i++)
            res += P[i] * (log2(P[i]));
        res = res * (-n);
        printf("%.10f\n", res);
    }
    else {
        dfs();
        double ans = 0.0;
        while (pq.size() > 1) {
            double a = pq.top();
            pq.pop();
            double b = pq.top();
            pq.pop();
            pq.push(a + b);
            ans += a + b;
        }
        printf("%.10f\n", ans);
    }
    return 0;
}
