#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

void z_value(const char *s, int *z, int n) {
    z[0] = n;
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        int x = max(0, min(z[i - l], r - i));
        while (i + x < n && s[x] == s[i + x])
            x++;
        z[i] = x;
        if (i + x > r)
            l = i, r = i + x;
    }
}

constexpr int maxn = 100000;
char s[maxn + 1];
unsigned long long fibo[101];

constexpr int nfibs = 27;
std::string fibs[nfibs];

unsigned long long solve2(int x, int a, int b) {
    x -= max(a, b) - 1;
    if (a > b) {
        if (b > 0)
            return x < 2 ? 0 : fibo[x - 1] - (x & 1);
        else if (a == 1) // b == 0
            return x < 2 ? 0 : fibo[x - 2];
        else // a > 1, b == 0
            return 0;
    } else if ((b - a) % 2 == 0) { // a <= b
        return x < 3 ? 0 : fibo[x - 3] - (x & 1);
    } else { // a <= b, (b - a) odd
        return x < 2 ? 0 : fibo[x - 2] - (~x & 1);
    }
}

unsigned long long solve(int n) {
    if (strcmp(s, "0") == 0)
        return n == 0 ? 1 : n == 1 ? 0 : fibo[n - 2];
    if (strcmp(s, "1") == 0)
        return n == 0 ? 0 : fibo[n - 1];
    if (strstr(s, "00"))
        return 0;

    int m = strlen(s);

    int si = 0;
    while ((int) fibs[si].size() < m)
        si++;

    std::string t1 = fibs[si] + s;
    vector<int> z1(t1.size());
    z_value(t1.data(), z1.data(), t1.size());

#if 0
    printf("t1 = %s\n", t1.data());
    for (int i = 0; i < (int) z1.size(); i++)
        printf("%d%c", z1[i], i == (int) z1.size() - 1 ? '\n' : ' ');
#endif

    std::string t2 = s + fibs[si];
    reverse(t2.begin(), t2.end());
    vector<int> z2(t2.size());
    z_value(t2.data(), z2.data(), t2.size());

    std::string t3 = s + fibs[si + 1];
    reverse(t3.begin(), t3.end());
    vector<int> z3(t3.size());
    z_value(t3.data(), z3.data(), t3.size());

    unsigned long long ans = 0;
    for (int i = 1; i < m; i++) {
        int a;
        if (z1[fibs[si].size() + i] == m - i) {
            a = 1;
            while ((int) fibs[a].size() < m - i)
                a++;
        } else if (i == m - 1 && s[i] == '0') {
            a = 0;
        } else {
            continue;
        }

        int b;
        if (z2[fibs[si].size() + (m - i)] == i) {
            b = si % 2;
            while ((int) fibs[b].size() < i)
                b += 2;
        } else if (z3[fibs[si + 1].size() + (m - i)] == i) {
            b = (si + 1) % 2;
            while ((int) fibs[b].size() < i)
                b += 2;
        } else {
            continue;
        }

#if 0
        printf("s=%s i=%d ba=%d'%d\n", s, i, b, a);
#endif
        ans += solve2(n, b, a);
    }

    return ans;
}

int main() {
    fibo[0] = fibo[1] = 1;
    for (int i = 2; i <= 100; i++)
        fibo[i] = fibo[i - 1] + fibo[i - 2];

    fibs[0] = "0";
    fibs[1] = "1";
    for (int i = 2; i < nfibs; i++)
        fibs[i] = fibs[i - 1] + fibs[i - 2];
    // assert(fibs[nfibs - 1].size() >= maxn);

    int n, kcase = 0;
    while (scanf("%d%s", &n, s) == 2) {
        printf("Case %d: %llu\n", ++kcase, solve(n));
    }
}
