#include <bits/stdc++.h>
using namespace std;

int main(){
    freopen("pour.in", "r", stdin);
    freopen("pour.out", "w", stdout);
    int n, a, b;
    scanf("%d%d%d", &n, &a, &b);
    b /= a;
    if (b&1) {
        if (n % b == 0)
            puts("2");
        else if ((n % b)&1)
            puts("2");
        else
            puts("1");
    }
    else {
        a = n / b;
        if (n % b == 0) {
            if (a&1)
                puts("1");
            else
                puts("2");
        }
        else if ((n % b)&1) {
            if (a&1)
                puts("1");
            else
                puts("2");
        }
        else {
            if (a&1)
                puts("2");
            else
                puts("1");
        }
    }
}
