#include <bits/stdc++.h>

using namespace std;

typedef pair<long long, long long> Pt;

constexpr long long inf = 64'000'000'000;

#define x first
#define y second

Pt operator + (const Pt &a, const Pt &b) {
    return {a.x + b.x, a.y + b.y};
}

Pt operator - (const Pt &a, const Pt &b) {
    return {a.x - b.x, a.y - b.y};
}

Pt operator * (const Pt &p, const long long &d) {
    return {p.x * d, p.y * d};
}

long long operator ^ (const Pt &a, const Pt &b) {
    return a.x * b.y - a.y * b.x;
}

int main() {
    int n;
    scanf("%d", &n);
    vector<Pt> ps;
    for (int i = 0; i < n; i++) {
        long long x, y;
        scanf("%lld%lld", &x, &y);
        ps.emplace_back(x, y);
    }

    long long weight = 0, centerx = 0, anchorx = ps[0].x, minx = inf, maxx = -inf;
    for (int i = 0; i < n; i++) {
        if (ps[i].y == 0) {
            minx = min(minx, ps[i].x);
            maxx = max(maxx, ps[i].x);
        }
        int i2 = (i + 1) % n;
        weight += (ps[i] ^ ps[i2]);
        centerx += (ps[i] + ps[i2]).x * (ps[i] ^ ps[i2]);
    }
    if (weight < 0) {
        weight = -weight;
        centerx = -centerx;
    }
    // x coord of centor = centerx / (3 * weight)
    // real weight = weight / 2

    long long minw = 0, maxw = inf;
    {
        // (minx - realcentorx) * realweight / (anchorx - minx) =
        // (minx - centerx / 3 / weight) * weight / 2 / (anchorx - minx) =
        // (minx * weight * 3 - centerx) / (6 * (anchorx - minx))
        long long dividend = minx * weight * 3 - centerx;
        long long divisor = 6 * (anchorx - minx);
        if (anchorx > minx) {
            minw = max(minw, dividend / divisor);
        } else if (anchorx < minx) {
            maxw = min(maxw, (dividend + divisor + 1) / divisor);
        } else if (dividend > 0) {
            minw = inf;
        }
    }
    {
        // (maxx - realcentorx) * realweight / (anchorx - maxx) =
        // (maxx - centerx / 3 / weight) * weight / 2 / (anchorx - maxx) =
        // (maxx * weight * 3 - centerx) / (6 * (anchorx - maxx))
        long long dividend = maxx * weight * 3 - centerx;
        long long divisor = 6 * (anchorx - maxx);
        if (anchorx < maxx) {
            minw = max(minw, dividend / divisor);
        } else if (anchorx > maxx) {
            maxw = min(maxw, (dividend + divisor - 1) / divisor);
        } else if (dividend < 0) {
            minw = inf;
        }
    }

    if (minw >= maxw) {
        puts("unstable");
    } else if (maxw >= inf) {
        printf("%lld .. inf\n", minw);
    } else {
        printf("%lld .. %lld\n", minw, maxw);
    } 
}
