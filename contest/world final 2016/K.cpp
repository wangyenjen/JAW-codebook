#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100 + 7;

int n;
int A[MAX_N];

bool check(int k) {
    static int B[MAX_N];
    for (int i = 0; i < n; i++)
        B[i] = A[i];
    int l = 0, r = n - 1;
    for (int i = k; i >= 1; i--) {
        if (l == r) {
            if (B[l] < 2 * i)
                return 0;
            B[l] -= 2 * i;
            if (B[l] == 0 && i > 1)
                return 0;
            continue;
        }
        if (B[l] < i || B[r] < i)
            return 0;
        B[l] -= i;
        B[r] -= i;
        if (B[l] == 0)
            l++;
        if (B[r] == 0)
            r--;
    }
    return 1;
}

int main() {
    scanf("%d", &n);
    int sum = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
        sum += A[i];
    }
    if (sum & 1) {
        puts("no quotation");
        return 0;
    }
    if (sum == 2) {
        puts("1");
        return 0;
    }
    int ans = -1;
    for (int k = 2; k <= 100; k++) {
        if (check(k))
            ans = k;
    }
    if (ans == -1)
        puts("no quotation");
    else
        printf("%d\n", ans);
    return 0;
}
