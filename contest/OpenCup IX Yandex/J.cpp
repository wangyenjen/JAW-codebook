#include <cstdio>
#include <utility>
using namespace std;

long long solve(int a, int b, long long c) {
    if (a < b)
        swap(a, b);
    // a >= b
    
    long long ans = 0;
    for (int quot = c / b, rem = c % b; quot >= 0; ) {
        ans += 1 + quot;

        rem -= a;
        while (rem < 0)
            quot--, rem += b;
    }

    return ans;
}

int main() {
    int a, b;
    long long c;
    while (scanf("%d%d%lld", &a, &b, &c) == 3)
        printf("%lld\n", solve(a, b, c));
}
