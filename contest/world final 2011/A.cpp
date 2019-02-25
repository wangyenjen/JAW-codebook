#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long;
constexpr ll inf = 1000000000000;

struct Sol {
    ll cost;
    vector<pair<bool, ll>> v; // true = mul

    Sol(): cost(), v() {}

    void mul(ll n = 1) {
        if (n == 0)
            return;
        if (v.empty() || !v.back().first)
            v.emplace_back(true, n);
        else
            v.back().second += n;

        cost += n;
    }

    void add(ll n = 1) {
        if (n == 0)
            return;
        if (v.empty() || v.back().first)
            v.emplace_back(false, n);
        else
            v.back().second += n;

        cost += n;
    }

    void print() const {
        for (auto p : v)
            printf(" %lld%c", p.second, p.first ? 'M' : 'A');
    }
};

bool operator < (const Sol &lhs, const Sol &rhs) {
    if (lhs.cost != rhs.cost)
        return lhs.cost < rhs.cost;
    for (int i = 0; i < (int) lhs.v.size(); i++) {
        auto l = lhs.v[i], r = rhs.v[i];
        if (l.first != r.first)
            return l.first < r.first;
        if (l.second != r.second)
            return (l.second > r.second) ^ l.first;
    }
    return false;
}

Sol go(int n, ll x, ll m) {
    Sol s;
    for (int i = 0; i < n; i++) {
        s.add(x % m);
        x /= m;
        s.mul();
    }
    s.add(x);
    reverse(s.v.begin(), s.v.end());
    return move(s);
}

void solve(int t, ll a, ll m, ll p, ll q, ll r, ll s) {
    if (r <= p && q <= s) {
        printf("Case %d: empty\n", t);
        return;
    }
    Sol best;
    best.cost = inf;

    ll mi = 1;
    for (int i = 0; ; i++, mi *= m) {
        if (q * mi > s)
            break;
        ll l = max(0LL, (r - p * mi + a - 1) / a);
        ll u = (s - q * mi) / a;

        ll mj = 1;
        for (int j = 0; l <= u; j++, mj *= m) {
            best = min(best, go(i, l, m));

            if (m == 1 || l == 0)
                break;

            l = (l + mj - 1) / mj * mj;
        }
        if (m == 1)
            break;
    }

    if (best.cost >= inf)
        printf("Case %d: impossible\n", t);
    else {
        printf("Case %d:", t);
        best.print();
        putchar('\n');
    }
}

int main() {
    int a, m, p, q, r, s;
    for (int t = 1; scanf("%d%d%d%d%d%d", &a, &m, &p, &q, &r, &s), a; t++)
        solve(t, a, m, p, q, r, s);
}
