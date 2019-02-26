#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100 + 7;
const int MAX_A = 1000000 + 7;

int A[MAX_N];
bool vis[MAX_A];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d", &A[i]);
        memset(vis, 0, sizeof(vis));
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                vis[abs(A[i] - A[j])] = 1;
        int ans = 0;
        for (int i = 2; i <= 10000; i++) {
            bool check = 1;
            for (int j = i; j <= 1000000; j += i) {
                if (vis[j]) {
                    check = 0;
                    break;
                }
            }
            if (check) {
                ans = i;
                break;
            }
        }
        if (ans) {
            puts("YES");
            for (int i = 0; i < n; i++)
                printf("%d%c", ans * i + 1, " \n"[i == n - 1]);
        }
        else
            puts("NO");
    }
    return 0;
}
