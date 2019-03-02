#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m;
    freopen("group.in", "r", stdin);
    scanf("%d%d", &n, &m);
    printf("%d %d\n", n - m, 3 * (n - m - 1) + (3 * m / 2));
    return 0;
}
