#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 300000 + 7;

map<ll, int> mp;

int get_id(char c) {
    if ('a' <= c && c <= 'z')
        return c - 'a';
    else
        return c - 'A' + 26;
}

char S[MAX_N];

int main() {
    freopen("hyperdrome.in", "r", stdin);
    freopen("hyperdrome.out", "w", stdout);
    int n;
    scanf("%d", &n);
    scanf("%s", S + 1);
    ll s = 0;
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        mp[s]++;
        s ^= (1ll << get_id(S[i]));
        if (mp.count(s))
            ans += mp[s];
        for (int j = 0; j < 52; j++) {
            ll t = s ^ (1ll << j);
            if (mp.count(t))
                ans += mp[t];
        }
    }
    printf("%lld\n", ans);
    return 0;
}
