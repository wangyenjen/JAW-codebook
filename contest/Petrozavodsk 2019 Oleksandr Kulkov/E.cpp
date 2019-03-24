#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    int s = 0;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        s += x - 2;
    }
    int ans = (s + 1) / 2 + n;
    printf("%d\n", ans);
    return 0;
}
