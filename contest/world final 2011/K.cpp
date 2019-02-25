#include <bits/stdc++.h>

using namespace std;

struct Point {
    int x, y;

    Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}

    bool operator < (const Point &rhs) const {
        return make_pair(x, y) < make_pair(rhs.x, rhs.y);
    }
};

typedef Point Vector;

Point operator + (Point p, Vector v) {
    return Point(p.x + v.x, p.y + v.y);
}

Vector operator - (Point a, Point b) {
    return Vector(a.x - b.x, a.y - b.y);
}

int cross(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

vector<Point> convex_hull(vector<Point> ps) {
    sort(ps.begin(), ps.end());
    int n = (int)ps.size();
    vector<Point> ch;
    int m = 0;
    for (int i = 0; i < n; i++) {
        while (m > 1 && cross(ps[i] - ch[m - 2], ch[m - 1] - ch[m - 2]) >= 0) {
            ch.pop_back();
            m--;
        }
        ch.push_back(ps[i]);
        m++;
    }
    int k = m;
    for (int i = n - 2; i >= 0; i--) {
        while (m > k && cross(ps[i] - ch[m - 2], ch[m - 1] - ch[m - 2]) >= 0) {
            ch.pop_back();
            m--;
        }
        ch.push_back(ps[i]);
        m++;
    }
    if (m > 1) {
        ch.pop_back();
        m--;
    }
    return ch;
}

int main() {
    int n, kcase = 0;
    while (scanf("%d", &n) != EOF && n) {
        vector<Point> ps;
        for (int i = 0; i < n; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            ps.push_back(Point(x, y));
        }
        ps = convex_hull(ps);
        // printf("haha %d\n", (int)ps.size());
        double ans = 1e20;
        for (int i = 0; i < (int)ps.size(); i++) {
            double pans = 0;
            Point p1 = ps[i], p2 = ps[(i + 1) % (int)ps.size()];
            for (Point p3 : ps) {
                pans = max(pans, fabs(1. * cross(p1 - p3, p2 - p3)) / hypot(p2.x - p1.x, p2.y - p1.y));
                // printf("(%d, %d), (%d, %d), (%d, %d): %.10f\n", p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, fabs(1. * cross(p1 - p3, p2 - p3)) / hypot(p2.x - p1.x, p2.y - p1.y) / 2);
            }
            ans = min(ans, pans);
        }
        printf("Case %d: %.2f\n", ++kcase, ans);
    }
    return 0;
}
