#pragma GCC optimize("O3")
#pragma GCC target("avx")
// #include <bits/stdc++.h>
#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <unordered_map>

using namespace std;

int P, t;
short table[100000000 + 7];

inline int power(int a, int n) {
    int x = 1;
    while (n) {
        if (n & 1)
            x = (long long)x * a % P;
        a = (long long)a * a % P;
        n >>= 1;
    }
    return x;
}

inline int bsgs(int X, int Y) {
    if (P == 2) {
        if (X == 0) {
            if (Y == 0)
                return 1;
            else 
                return 0;
        }
        else {
            if (Y == 0)
                return -1;
            else
                return 0;
        }
    }
    if (X == 0) {
        if (Y == 0)
            return 1;
        else if (Y == 1)
            return 0;
        else
            return -1;
    }
    /*
    vector<pair<ll, int> > table;
    ll tt = 1;
    for (int i = 0; i < t; i++, tt = tt * X % P) {
        table.emplace_back(tt, i);
    }
    sort(table.begin(), table.end());
    tt = power(tt, P - 2);
    for (int i = 0; i <= t; i++) {
        auto it = lower_bound(table.begin(), table.end(), make_pair(Y, 0));
        if (it == table.end() || it->first != Y) {
            Y = Y * tt % P;
            continue;
        }
        return i * t + it->second;
    }
    */
    // unordered_map<int, int> table;
    int tt = 1;
    vector<int> vs;
    for (int i = 0; i < t; i++, tt = (long long)tt * X % P) {
        // table.insert(make_pair(tt, i));
        vs.push_back(tt);
        if (table[tt] == -1)
            table[tt] = i;
    }
    int ans = -1;
    tt = power(tt, P - 2);
    for (int i = 0; i <= t; i++) {
        if (table[Y] != -1) {
            ans = i * t + table[Y];
            break;
        }
        Y = (long long)Y * tt % P;
    }
    for (int x : vs)
        table[x] = -1;
    return ans;
}

int main() {
    memset(table, -1, sizeof(table));
    freopen("alot.in", "r", stdin);
    freopen("alot.out", "w", stdout);
    int Q;
    scanf("%d%d", &P, &Q);
    t = (int)(sqrt(P) + 0.5);
    while (Q--) {
        int X, Y;
        scanf("%d%d", &X, &Y);
        int ans = bsgs(X, Y);
        printf("%d\n", ans);
    }
    return 0;
}
