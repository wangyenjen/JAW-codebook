#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll p;

ll power(ll a, ll n) {
    ll x = 1;
    while (n) {
        if (n & 1)
            x = x * a % p;
        a = a * a % p;
        n >>= 1;
    }
    return x;
}

ll meow(ll k) {
    if (k == 1)
        return 1;
    else {
        ll x = meow(k / 2);
        ll t = power(10, k / 2);
        ll res = (x + x * t % p) % p;
        if (k % 2 == 1)
            res += power(10, k - 1);
        if (res >= p) 
            res -= p;
        return res;
    }
}

int main() {
    freopen("zeroes.in", "r", stdin);
    freopen("zeroes.out", "w", stdout);
    ll k;
    scanf("%lld%lld", &k, &p);
    if (k == 1)
        puts("1");
    else if (p == 2)
        printf("%lld\n", (k + 1) % 2);
    else if (p == 3)
        printf("%lld\n", k % 3);
    else if (p == 5)
        printf("%lld\n", (k + 4) % 5);
    else
        printf("%lld\n", (k % p * power(10, k - 1) % p - meow(k) + p + k % p) % p);
    return 0;
}
