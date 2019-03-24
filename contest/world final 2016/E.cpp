#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll y, l;

bool check1(ll b) {
    ll x = y;
    vector<ll> vs;
    while (x) {
        ll t = x % b;
        if (t >= 10)
            return 0;
        vs.push_back(x % b);
        x /= b;
    }
    ll t = 0;
    for (int i = (int)vs.size() - 1; i >= 0; i--)
        t = t * 10 + vs[i];
    return t >= l;
}

vector<ll> calc(ll x, ll b) {
    vector<ll> vs;
    while (x) {
        ll t = x % b;
        vs.push_back(t);
        x /= b;
    }
    return vs;
}

int main() {
    scanf("%lld%lld", &y, &l);
    ll ans = -1;
    for (ll b = 10; b <= 1000000; b++) {
        if (check1(b)) 
            ans = b;
    }
    for (ll l2 = l; l2 <= 1000; l2++) {
        ll lb = 10, rb = 1000000000000000000ll;
        while (lb < rb) {
            ll mid = (lb + rb + 1) / 2;
            vector<ll> vs = calc(y, mid);
            vector<ll> vs2 = calc(l2, 10);
            if ((int)vs.size() != (int)vs2.size()) {
                if ((int)vs.size() > (int)vs2.size())
                    lb = mid;
                else
                    rb = mid - 1;
                continue;
            }
            bool ok = 1;
            for (int i = (int)vs.size() - 1; i >= 0; i--) {
                if (vs[i] != vs2[i]) {
                    if (vs[i] > vs2[i]) {
                        ok = 1;
                        break;
                    }
                    else {
                        ok = 0;
                        break;
                    }
                }
            }
            if (ok)
                lb = mid;
            else
                rb = mid - 1;
        }

        vector<ll> vs = calc(y, lb);
        vector<ll> vs2 = calc(l2, 10);
        bool ok = ((int)vs.size() == (int)vs2.size());
        for (int i = (int)vs.size() - 1; i >= 0 && ok; i--) {
            if (vs[i] != vs2[i]) {
                ok = 0;
                break;
            }
        }
        if (ok)
            ans = max(ans, lb);
    }
    printf("%lld\n", ans);
    return 0;
}
