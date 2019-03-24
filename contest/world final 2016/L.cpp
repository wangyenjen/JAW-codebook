#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

pair<ll, ll> calc(vector<pair<ll, ll> > vs) {
    ll ans = 0, sum = 0;
    sort(vs.begin(), vs.end());
    for (pair<ll, ll> p : vs) {
        if (sum < p.first){
            ans += p.first - sum;
            sum = p.first;
        }
        sum += p.second - p.first;
    }
    /*
    ll lb = 0, rb = 2e15;
    while (lb < rb) {
        ll mid = (lb + rb) >> 1;
        bool ok = 1;
        ll sum = mid;
        for (pair<ll, ll> p : vs) {
            if (sum >= p.first) 
                sum += p.second - p.first;
            else {
                ok = 0;
                break;
            }
        }
        if (ok)
            rb = mid;
        else
            lb = mid + 1;
    }
    ans = (lb + rb) / 2;
    */
    ll d = 0;
    for (pair<ll, ll> p : vs)
        d += p.second - p.first;
    return make_pair(ans, d);
}

int main() {
    int n;
    scanf("%d", &n);
    vector<pair<ll, ll> > v1, v2;
    for (int i = 0; i < n; i++) {
        ll a, b;
        scanf("%lld%lld", &a, &b);
        if (a <= b)
            v1.emplace_back(a, b);
        else
            v2.emplace_back(b, a);
    }
    ll s1, d1, s2, d2;
    tie(s1, d1) = calc(v1);
    tie(s2, d2) = calc(v2);
    printf("%lld\n", max(s1, s2 + d2 - d1));
    return 0;
}
