#include <cstdio>
#include <algorithm>
using namespace std;

struct P {
    int x, y;
    void read() {
        scanf("%d%d", &x, &y);
    }
    bool operator < (P p) const {
        return make_pair(x - y, x) < make_pair(p.x - p.y, p.x);
    }
} p[100000];

int method1(int l, int r, int n) {
    int ans = 0;

    for (int i = l; i < r; i++)
        for (int j = i + 1; j < r; j++)
            if (binary_search(p, p + l, P{p[i].x, p[j].y}) &&
                binary_search(p + r, p + n, P{p[j].x, p[i].y})) {

                ans++;
            }
    return ans;
}
int method2(int l, int r, int n) {
    int ans = 0, dxy = p[l].x - p[l].y;

    for (int i = 0; i < l; i++) {
        int x = p[i].x, y = p[i].y;
        if (binary_search(p + l, p + r, P{x, x - dxy}) &&
            binary_search(p + l, p + r, P{y + dxy, y}) &&
            binary_search(p + r, p + n, P{y + dxy, x - dxy})) {

            ans++;
        }
    }

    return ans;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        p[i].read();

    sort(p, p + n);

    int ans = 0;
    for (int i = 0; i < n; ) {
        int j = i + 1;
        while (j < n && p[i].x - p[i].y == p[j].x - p[j].y)
            j++;

        int m = j - i;
        if (m * m <= n) {
            ans += method1(i, j, n);
        } else {
            ans += method2(i, j, n);
        }

        i = j;
    }
    printf("%d\n", ans);
}
