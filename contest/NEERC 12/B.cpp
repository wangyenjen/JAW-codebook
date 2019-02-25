#include <algorithm>
#include <cstdio>
#include <map>
#include <utility>
#include <vector>
using namespace std;

#ifdef JOHNCHEN902
int _v[] = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1000};
int _n = size(_v);
int _c = 99;
int _a = (1 << _n) - 1;
int _b = _a ^ (1 << (rand() % _n));

int _sum() {
    int s = 0;
    for (int i = 0; i < _n; i++)
        if (_b & (1 << i))
            s += _v[i];
    return s;
}

void init(int &n, int &c, int &b) {
    n = _n;
    c = _c;
    b = _sum();
}

int accept() {
    _a = _b;
    _b = _a ^ (1 << (rand() % _n));
    return _sum();
}

int decline() {
    _b = _a ^ (1 << (rand() % _n));
    return _sum();
}

[[noreturn]] void stop() {
    printf("STOPPED AT _b=%d _sum()=%d\n", _b, _sum());
    exit(0);
}

#else

constexpr int max_moves = 1000;
int moves;

void init(int &n, int &c, int &b) {
    scanf("%d%d%d", &n, &c, &b);
    moves = 0;
}

[[noreturn]] void stop() {
    puts("stop");
    exit(0);
}

int accept() {
    puts("accept");
    fflush(stdout);
    int x;
    scanf("%d", &x);
    moves++;
    
    if (moves == max_moves)
        stop();

    return x;
}

int decline() {
    puts("decline");
    fflush(stdout);
    int x;
    scanf("%d", &x);
    moves++;

    if (moves == max_moves)
        stop();

    return x;
}
#endif

int v[20];
int dp[1 << 20];

int main() {
    int n, c, a, b;
    init(n, c, a);
    b = accept();

    while (a) {
        if (b < a) {
            a = b;
            b = accept();
        } else {
            b = decline();
        }
    }

    // now a = 0

    for (int i = 0; i < n; i++) {
        while (b < a)
            b = decline();
        v[i] = b - a;
        // fprintf(stderr, "v[%d]=%d\n", i, v[i]);
        a = b;
        b = accept();
    }

    // now a = max, all numbers are known

    for (int i = 0; i < n; i++)
        for (int j = 0; j < (1 << i); j++)
            dp[j + (1 << i)] = dp[j] + v[i];

    int bi = 0;
    for (int i = 1; i < (1 << n); i++)
        if (dp[i] <= c && dp[i] > dp[bi])
            bi = i;
    int opt = dp[bi];

    if (opt == a) {
        a = b;
        b = accept();
        do {
            b = decline();
        } while (b != opt);
        stop();
    }

    while (true) {
        if (b == opt)
            stop();

        if (b > a) {
            b = decline();
            continue;
        }

        int w = a - b;
        int found = -1;
        for (int i = 0; i < n; i++)
            if (v[i] == w && !(bi & (1 << i))) {
                found = i;
                break;
            }

        if (found >= 0) {
            bi |= 1 << found;
            a = b;
            b = accept();
        } else {
            b = decline();
        }
    }
}
