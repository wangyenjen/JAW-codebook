#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2000 + 7;
const double PI = acos(-1);

struct Point {
    int x, y;

    Point(double _x = 0, int _y = 0) : x(_x), y(_y) {}
};

typedef Point Vector;

Point operator + (Point p, Vector v) {
    return Point(p.x + v.x, p.y + v.y);
}

Vector operator - (Point a, Point b) {
    return Vector(a.x - b.x, a.y - b.y);
}

int n;
vector<pair<Point, Point> > vs;
int calc(Point ori, int w_base) {
    int ans = w_base;
    vector<pair<double, int> > es;
    for (int i = 0; i < (int)vs.size(); i++) {
        if (vs[i].first.y == ori.y)
            continue;
        double lb, rb;
        if (vs[i].first.y > ori.y) {
            lb = atan2(vs[i].second.y - ori.y, vs[i].second.x - ori.x);
            rb = atan2(vs[i].first.y - ori.y, vs[i].first.x - ori.x);
        }
        else {
            lb = atan2(vs[i].first.y - ori.y, vs[i].first.x - ori.x);
            rb = atan2(vs[i].second.y - ori.y, vs[i].second.x - ori.x);
        }

        if (lb < 0)
            lb += 2 * PI;
        if (rb < 0)
            rb += 2 * PI;

        es.emplace_back(lb, -(vs[i].second.x - vs[i].first.x));
        es.emplace_back(rb, -(vs[i].first.x - vs[i].second.x));

        lb += PI;
        rb += PI;
        if (lb > 2 * PI)
            lb -= 2 * PI;
        if (rb > 2 * PI)
            rb -= 2 * PI;

        es.emplace_back(lb, -(vs[i].second.x - vs[i].first.x));
        es.emplace_back(rb, -(vs[i].first.x - vs[i].second.x));
    }
    sort(es.begin(), es.end());

    int w = 0;
    for (int i = 0; i < (int)es.size(); i++) {
        w -= es[i].second;
        ans = max(ans, w + w_base);
    }

    return ans;
}

int main() {
    scanf("%d", &n);
    vector<pair<Point, int> > ps;
    for (int i = 0; i < n; i++) {
        int x1, x2, y;
        scanf("%d%d%d", &x1, &x2, &y);
        if (x1 > x2)
            swap(x1, x2);
        vs.emplace_back(Point(x1, y), Point(x2, y));
        ps.emplace_back(Point(x1, y), x2 - x1);
        ps.emplace_back(Point(x2, y), x2 - x1);
    }
    
    int ans = 0;
    for (auto p : ps) {
        ans = max(ans, calc(p.first, p.second));
    }

    printf("%d\n", ans);

    return 0;
}
