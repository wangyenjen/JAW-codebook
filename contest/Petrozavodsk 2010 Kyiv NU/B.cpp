#include <cstdio>
#include <algorithm>
using namespace std;

constexpr int mod = 1000000007;

struct P {
    int x, y;
    void read() {
        scanf("%d%d", &x, &y);
    }

} a[10000], b[5000];

long long cross(P p1, P p2, P p3) {
    int x1 = p2.x - p1.x, x2 = p3.x - p2.x;
    int y1 = p2.y - p1.y, y2 = p3.y - p2.y;
    return (long long) x1 * y2 - (long long) x2 * y1;
}

bool check(int l, int r, int m) {
    return all_of(b, b + m,
            [l, r](P p) {
                return cross(a[l], a[r], p) > 0;
            });
}

int lst[10000];
int dp[5000];
int sdp[5001];

int main() {
    freopen("drawing.in", "r", stdin);
    freopen("drawing.out", "w", stdout);

    int n, m;
    scanf("%d%d", &n, &m);

    if (m == 0) {
        int ans = 1;
        for (int i = 0; i < n; i++)
            ans = ans * 2 % mod;
        ans = (ans - 1 - n - n * (n - 1) / 2 + mod) % mod;
        printf("%d\n", ans);
        return 0;
    }

    for (int i = 0; i < n; i++)
        a[i].read();
    for (int j = 0; j < m; j++)
        b[j].read();

    if (cross(a[0], a[1], a[2]) < 0) {
        // fprintf(stderr, "clockwise\n");
        reverse(a, a + n);
    }

    copy_n(a, n, a + n);

    for (int l = 0, r = 1; r < 2 * n; r++) {
        while (l + 1 < r && !check(l, r, m))
            l++;
        lst[r] = l;

        // fprintf(stderr, "lst[%d]=%d\n", r, l);
    }

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
        sdp[i] = 0;
        sdp[i + 1] = sdp[i] + dp[i];
        for (int j = i + 1; j < n; j++) {
            dp[j] = (sdp[j] - sdp[max(i, lst[j])] + mod) % mod;
            sdp[j + 1] = (sdp[j] + dp[j]) % mod;
            if (lst[n + i] <= j)
                ans += dp[j];
        }
    }
    printf("%d\n", int(ans % mod));
}
