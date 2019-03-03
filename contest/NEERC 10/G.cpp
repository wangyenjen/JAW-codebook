#include <cstdio>
#include <tuple>
using namespace std;

tuple<bool, int, int, int> go1(int (&x)[4][4], int r) {
    int pos = -1, sum = 0;
    for (int i = 0; i < 4; i++) {
        if (x[r][i] == 11) {
            if (pos >= 0)
                return make_tuple(false, 0, 0, 0);
            pos = i;
        } else {
            sum += x[r][i];
        }
    }

    if (pos < 0 || sum < 6 || sum > 9)
        return make_tuple(false, 0, 0, 0);

    return make_tuple(true, r, pos, 10 - sum);
}
tuple<bool, int, int, int> go2(int (&x)[4][4], int c) {
    int pos = -1, sum = 0;
    for (int i = 0; i < 4; i++) {
        if (x[i][c] == 11) {
            if (pos >= 0)
                return make_tuple(false, 0, 0, 0);
            pos = i;
        } else {
            sum += x[i][c];
        }
    }

    if (pos < 0 || sum < 6 || sum > 9)
        return make_tuple(false, 0, 0, 0);

    return make_tuple(true, pos, c, 10 - sum);
}

tuple<bool, int, int, int> go(int (&x)[4][4], int r, int c) {
    auto t = go1(x, r);
    if (get<0>(t))
        return t;
    return go2(x, c);
}

int main() {
#if 0
#ifndef LOCAL
    freopen("dome.in", "r", stdin);
    freopen("dome.out", "w", stdout);
#endif
#endif
    int x[4][4];
    for (int i = 0; i < 4; i++)
        fill_n(x[i], 4, 11);

    while (true) {
        int r, c, k;
        scanf("%d%d%d", &r, &c, &k);
        r--, c--;
        x[r][c] = k;

        bool ok;
        int ar, ac, ak;
        tie(ok, ar, ac, ak) = go(x, r, c);

        if (ok) {
            printf("%d %d %d WIN\n", ar + 1, ac + 1, ak);
            fflush(stdout);
            break;
        }

        printf("%d %d %d\n", r + 1, 3 - c + 1, 5 - k);
        fflush(stdout);
        x[r][3 - c] = 5 - k;
    }
}
