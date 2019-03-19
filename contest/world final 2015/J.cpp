#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 1 << 20;

typedef long double ld;
typedef complex<ld> cplx;
const ld PI = acosl(-1);
const cplx I(0, 1);

cplx omega[MAX_N + 1];

void pre_fft() {
    for (int i = 0; i <= MAX_N; i++)
        omega[i] = exp(i * 2 * PI / MAX_N * I);
}

void fft(int n, cplx a[], bool inv = false) {
    int basic = MAX_N / n;
    int theta = basic;
    for (int m = n; m >= 2; m >>= 1) {
        int mh = m >> 1;
        for (int i = 0; i < mh; i++) {
            cplx w = omega[inv ? MAX_N - (i * theta % MAX_N) : i * theta % MAX_N];
            for (int j = i; j < n; j += m) {
                int k = j + mh;
                cplx x = a[j] - a[k];
                a[j] += a[k];
                a[k] = w * x;
            }
        }
        theta = theta * 2 % MAX_N;
    }

    int i = 0;
    for (int j = 1; j < n - 1; j++) {
        for (int k = n >> 1; k > (i ^= k); k >>= 1);
        if (j < i)
            swap(a[i], a[j]);
    }
    if (inv)
        for (i = 0; i < n; i++)
            a[i] /= n;
}

cplx A[MAX_N];
int C[MAX_N];
ll f[MAX_N];

int main() {
    pre_fft();
    for (int i = 1; i <= 500000; i++) {
        for (int j = i; j <= 500000; j += i)
            C[j]++;
    }
    for (int i = 1; i <= 500000; i++)
        A[i] = C[i];
    fft(MAX_N, A);
    for (int i = 0; i < MAX_N; i++)
        A[i] *= A[i];
    fft(MAX_N, A, true);
    for (int i = 1; i <= 500000; i++)
        f[i] = (ll)(real(A[i]) + 0.5);
    int n;
    scanf("%d", &n);
    while (n--) {
        int l, r;
        scanf("%d%d", &l, &r);
        int best = l;
        for (int i = l; i <= r; i++) {
            if (f[best] < f[i])
                best = i;
        }
        printf("%d %lld\n", best, f[best]);
    }
    return 0;
}
