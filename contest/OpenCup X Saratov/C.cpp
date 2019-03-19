#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 300 + 7;
const double INF =  1e30;

struct Point {
    int x, y;
    
    Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
};

typedef Point Vector;

Point operator + (Point a, Vector b) {
    return Point(a.x + b.x, a.y + b.y);
}

Vector operator - (Point a, Point b) {
    return Vector(a.x - b.x, a.y - b.y);
}

int sqr(int x) {
    return x * x;
}

double dist(Point a, Point b) {
    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

int cross(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

int dot(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

double dp[MAX_N][MAX_N];

int main() {
    freopen("mines.in", "r", stdin);
    freopen("mines.out", "w", stdout);
    int N, K;
    scanf("%d%d", &N, &K);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            dp[i][j] = INF;
    }
    vector<Point> ps1, ps2;
    for (int i = 0; i < N; i++) {
        int x, y;
        scanf("%d%d", &x, &y); 
        ps1.push_back(Point(x, y));
    }
    for (int i = 0; i < K; i++) {
        int x, y;
        scanf("%d%d", &x, &y); 
        ps2.push_back(Point(x, y));
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (j == i)
                continue;
            int sign = 1;
            bool ok = 1;
            for (Point p : ps2) {
                int t = cross(ps1[j] - ps1[i], p - ps1[i]);
                if (t > 0)
                    t = 1;
                else if (t < 0)
                    t = -1;
                if (t == 0)
                    continue;
                if (sign == 0)
                    sign = t;
                else if (sign != t) {
                    ok = 0;
                    break;
                }
            }
            if (ok) {
                dp[i][j] = min(dp[i][j], dist(ps1[i], ps1[j]));
            }
        }
    }
    double ans = INF;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (j == i)
                continue;
            int flag = 1;
            int flag2 = 1;
            for (Point p : ps2) {
                if (cross(p - ps1[i], p - ps1[j]) != 0)
                    flag2 = 0;
                if (cross(p - ps1[i], p - ps1[j]) == 0 && dot(p - ps1[i], p - ps1[j]) <= 0)
                    continue;
                flag = 0;
                break;
            }
            if (flag)
                ans = min(ans, dist(ps1[i], ps1[j]) * 2);
            else if (flag2) 
                dp[i][j] = INF;
        }
    }
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (k == j || k == i)
                    continue;
                // if (cross(ps1[j] - ps1[k], ps1[k] - ps1[i]) != 0)
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
            }
        }
    }
    for (int i = 0; i < N; i++)
        ans = min(ans, dp[i][i]);
    if (ans > 1e20)
        puts("-1");
    else
        printf("%.10f\n", ans);
    return 0;
}
