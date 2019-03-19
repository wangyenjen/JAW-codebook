#include <bits/stdc++.h>
using namespace std;

long long fact[21];

long long comb(int a, int b) {
    return fact[a] / (fact[b] * fact[a - b]);
}

int main() {
    fact[0] = 1;
    for (int i = 1; i <= 20; i++)
        fact[i] = fact[i - 1] * i;

    int n;
    scanf("%d", &n);

    double p[4];
    for (int i = 0; i < 4; i++)
        scanf("%lf", &p[i]);

    using P = pair<double, long long>;
    priority_queue<P, vector<P>, greater<P>> pq;
    for (int i = 0; i <= n; i++)
        for (int j = i; j <= n; j++)
            for (int k = j; k <= n; k++)
                pq.emplace(pow(p[0], i) * pow(p[1], j - i) * pow(p[2], k - j) * pow(p[3], n - k),
                           comb(n, i) * comb(n - i, j - i) * comb(n - j, k - j));

    double ans = 0.0;
    while (pq.size() > 1 || pq.top().second > 1) {
        if (pq.top().second > 1) {
            auto [a, an] = pq.top();
            pq.pop();

            pq.emplace(a * 2, an / 2);
            ans += a * (an / 2 * 2);
            if (an % 2)
                pq.emplace(a, 1);
        } else {
            auto [a, an] = pq.top();
            pq.pop();
            auto [b, bn] = pq.top();
            pq.pop();

            // 1 = an <= bn
            pq.emplace(a + b, 1);
            ans += a + b;
            if (an < bn)
                pq.emplace(b, bn - 1);
        }
    }
    printf("%.10f\n", ans);
}
