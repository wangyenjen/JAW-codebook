#pragma GCC optimize("O3")
#pragma GCC target("avx")
#include <bits/stdc++.h>

using namespace std;

typedef long double Type;
typedef long long ll;

const int MAX_W = 10000 + 7;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const Type EPS = 1e-13;

int dcmp(Type x) {
    return fabsl(x) < EPS ? 0 : x > 0 ? 1 : -1;
}

ll dp[MAX_W];
vector<pair<int, int> > D[MAX_W];
vector<pair<int, int> > C;

Type calc(int w) {
    static const int TIMES = 300;

    Type lb = 20000, rb = -2e8;
    for (int times = 0; times < TIMES; times++) {
        Type tmp = 0;
        Type mid = (lb + rb) / 2.0;
        for (pair<int, int> p : C) {
            if (dcmp(p.first - mid) >= 0) {
                if (p.second == 0)
                    tmp += 20000;
                else
                    tmp += (p.first - mid) / p.second;
            }
        }
        if (tmp >= w)
            rb = mid;
        else
            lb = mid;
    }
    Type area = 0.0;
    Type len = 0.0;
    Type mid = (lb + rb) / 2.0;
    bool zero = 0;
    for (auto p : C) {
        if (dcmp(p.first - mid) >= 0) {
            if (p.second != 0) {
                area += ((Type)p.first * (Type)p.first - mid * mid) / p.second / 2;
                len += (p.first - mid) / p.second;
            }
            else {
                zero = 1;
            }
        }
    }
    if (zero)
        area += mid * (w - len);
    return area;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int i = 0; i < MAX_W; i++)
        dp[i] = -INF;
    dp[0] = 0;
    int n, w;
    cin >> n >> w;
    for (int i = 0; i < n; i++) {
        char op;
        cin >> op;
        if (op == 'D') {
            int a, b, c;
            cin >> a >> b >> c;
            D[a].emplace_back(b, c);
        }
        else {
            int a, b;
            cin >> a >> b;
            C.emplace_back(a, b);
        }
    }
    for (int i = 1; i <= w; i++) {
        if (D[i].empty())
            continue;
        int m = w / i;
        priority_queue<pair<int, int>, vector<pair<int, int> > > pq;
        for (pair<int, int> p : D[i])
            pq.push(p);
        while (m--) {
            pair<ll, ll> p = pq.top();
            pq.pop();
            for (int j = w; j >= i; j--) {
                if (dp[j - i] != -INF)
                    dp[j] = max(dp[j], dp[j - i] + p.first);
            }
            p.first -= p.second;
            pq.push(p);
        }
    }
    if (C.empty() && dp[w] == -INF) {
        cout << "impossible\n";
    }
    else if (C.empty()) {
        cout << fixed << setprecision(10) << dp[w] << '\n';
    }
    else {
        Type ans = -1e30;
        for (int i = 0; i <= w; i++) {
            // printf("%d: %lld %.10f\n", i, dp[i], calc(w - i));
            ans = max(ans, dp[i] + calc(w - i));
        }
        cout << fixed << setprecision(10) << ans << '\n';
    }
    return 0;
}
