#include <bits/stdc++.h>

using namespace std;

typedef long double Type;

const Type EPS = 1e-12;
const int MAX_N = 100000 + 7;

int n, p, q;
vector<pair<int, int> > vs;

Type my_fabs(Type x) {
    return x < 0 ? -x : x;
}

int dcmp(Type x) {
    return my_fabs(x) < EPS ? 0 : x > 0 ? 1 : -1;
} 

bool check(Type x) {
    int meow = 0;
    for (int i = 0; i < n; i++) {
        Type t = vs[i].second - x * (i + 1);
        if (vs[i].first - x * i > vs[meow].first - x * meow)
            meow = i;
        Type mx = vs[meow].first - x * meow;
        if (dcmp(t - mx) <= 0) {
            p = vs[i].second - vs[meow].first;
            q = i - meow + 1;
            return 1;
        }
    }
    return 0;
}


int main() {
    freopen("caravan.in", "r", stdin);
    freopen("caravan.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        vs.emplace_back(a, b);
    }
    sort(vs.begin(), vs.end());

    Type lb = 0.0, rb = 1000000.0;
    p = -1, q = -1;
    for (int times = 0; times < 100; times++) {
        Type mid = (lb + rb) / 2.0;
        if (check(mid))
            rb = mid;
        else 
            lb = mid;
    }

    assert(p != -1 && q != -1);
    int d = __gcd(p, q);
    p /= d;
    q /= d;
    printf("%d/%d\n", p, q);

    return 0;
}
