#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll power(ll a, ll n) {
    ll x = 1;
    while (n) {
        if (n & 1)
            x = x * a;
        a = a * a;
        n >>= 1;
    }
    return x;
}

int main() {
    freopen("great.in", "r", stdin);
    freopen("great.out", "w", stdout);
    ll n, k;
    scanf("%lld%lld", &n, &k);
    vector<ll> a;
    ll t = n;
    while (t) {
        a.push_back(t % k);
        t /= k;
    }
    int l = (int)a.size() - 1;
    if (l & 1) {
        printf("%lld\n", power(k, (l + 1) / 2));
    }
    else {
        ll ans = 0;
        for (int i = l; i >= 0; i -= 2) {
            if(i == 0 || (i > 0 && a[i - 1] > 0)){
                ans += power(k, i / 2) * (a[i] + 1);
                break;
            }
            else
                ans += power(k, i / 2) * a[i];
        }
        printf("%lld\n", ans);
    }
    return 0;
}
