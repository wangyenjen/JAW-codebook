#include <cstdio>
#include <numeric>
#include <algorithm>
using namespace std;

constexpr long long inf = 2'000'000'000'000'000;

struct Node {
    char name[11];
    int x, d, deg, deg2;
    int ans;
    long long d2sea;
    long long d2src;
} a[1000000];

int top[1000000];
int xsea[500000];
int xsrc[1000000];

template<typename T>
void minify(T &l, T r) { l = min(l, r); }
template<typename T>
void maxify(T &l, T r) { l = max(l, r); }

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%10s%d%d", a[i].name, &a[i].x, &a[i].d);
        a[i].x += n;
    }

    int sea = n;

    for (int i = n + 1; i <= n + m; i++) {
        scanf("%d%d", &a[i].x, &a[i].d);
        a[i].x += n;
    }

    for (int i = 0; i <= n + m; i++)
        if (i != sea)
            a[a[i].x].deg++;

    for (int i = 0; i <= n + m; i++)
        a[i].deg2 = a[i].deg;

    iota(top, top + n, 0);
    for (int l = 0, r = n; l < n + m; l++)
        if (--a[a[top[l]].x].deg2 == 0)
            top[r++] = a[top[l]].x;

    a[sea].d2sea = 0;
    for (int i = n + m - 1; i >= 0; i--)
        a[top[i]].d2sea = a[top[i]].d + a[a[top[i]].x].d2sea;

    for (int i = n; i <= n + m; i++)
        a[i].d2src = inf;
    for (int i = 0; i < n + m; i++) {
        a[top[i]].d2src += a[top[i]].d;
        minify(a[a[top[i]].x].d2src, a[top[i]].d2src);
    }
    for (int i = 0; i < n + m; i++)
        maxify(a[a[top[i]].x].d2src, a[top[i]].d2src);

    iota(xsea, xsea + n, 0);
    sort(xsea, xsea + n, [](int l, int r) { return a[l].d2sea < a[r].d2sea; });
    iota(xsrc, xsrc + n, 0);
    iota(xsrc + n, xsrc + n + m, n + 1);
    sort(xsrc, xsrc + n + m, [](int l, int r) { return a[l].d2src < a[r].d2src; });

    for (int i = 0; i <= n + m; i++)
        a[i].deg2 = a[i].deg;

    int ans = n + 1;

    for (int i = 0, j = 0; i < n; i++) {
        // fprintf(stderr, ">>> %d %s\n", xsea[i], a[xsea[i]].name);
        for (; j < n + m && a[xsrc[j]].d2src <= a[xsea[i]].d2sea; j++) {
            int p = a[xsrc[j]].x;
            // fprintf(stderr, "Remove %d -> %d\n", xsrc[j], p);
            if (--a[p].deg2 >= (p != sea))
                ans--;
        }
        // fprintf(stderr, "ans = %d\n", ans);

        a[xsea[i]].ans = ans;
    }

#if 0
    for (int i = 0; i <= n + m; i++)
        printf("d2sea[%d] = %lld\n", i, a[i].d2sea);
    for (int i = 0; i <= n + m; i++)
        printf("d2src[%d] = %lld\n", i, a[i].d2src);
#endif
    for (int i = 0; i < n; i++)
        printf("%s %d\n", a[i].name, a[i].ans);
}
