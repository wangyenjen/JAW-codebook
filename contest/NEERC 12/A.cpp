#include <cstdio>
using namespace std;
int a[9];
int b[10][10];
int main() {
#ifndef JOHNCHEN902
    freopen("addictive.in", "r", stdin);
    freopen("addictive.out", "w", stdout);
#endif
    int h, w, c;
    scanf("%d%d%d", &h, &w, &c);
    for (int i = 0; i < c; i++)
        scanf("%d", a + i);

    for (int i = 0, k = 0; i < h; i++) {
        int begin, end, step;
        if (i % 2 == 0)
            begin = 0, end = w, step = 1;
        else
            begin = w - 1, end = -1, step = -1;

        for (int j = begin; j != end; j += step) {
            while (a[k] == 0)
                k++;
            a[k]--;
            b[i][j] = k;
        }
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++)
            putchar('1' + b[i][j]);
        putchar('\n');
    }
}
