#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int table[81][81];

vector<ll> dq(vector<ll> &a, vector<ll> &b) {
    int n = (int)a.size();
    vector<ll> res(n, 0);

    if (n <= 81) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                res[table[i][j] % n] += a[i] * b[j]; 
            }
        }

        return res;
    }

    int m = n / 3;

    vector<ll> f0(m), f1(m), f2(m);
    vector<ll> g0(m), g1(m), g2(m);
    
    for (int i = 0; i < m; i++) {
        f0[i] = a[i];
        f1[i] = a[m + i];
        f2[i] = a[m + m + i];

        g0[i] = b[i];
        g1[i] = b[m + i];
        g2[i] = b[m + m + i];
    }

    vector<ll> t1(m), t2(m), t3(m), t4(m);

    for (int i = 0; i < m; i++)
        t1[i] = f1[i] + f2[i];

    for (int i = 0; i < m; i++)
        t2[i] = g1[i] + g2[i];

    for (int i = 0; i < m; i++)
        t3[i] = f0[i] + f1[i] + f2[i];

    for (int i = 0; i < m; i++)
        t4[i] = g0[i] + g1[i] + g2[i];

    vector<ll> t5 = dq(f0, g1);
    vector<ll> t6 = dq(f1, g0);

    vector<ll> A = dq(t1, t2);

    vector<ll> B(m, 0);
    for (int i = 0; i < m; i++)
        B[i] = t5[i] + t6[i];

    vector<ll> C = dq(t3, t4);
    for (int i = 0; i < m; i++)
        C[i] -= (A[i] + B[i]);

    for (int i = 0; i < m; i++) {
        res[i] = A[i];
        res[i + m] = C[i];
        res[i + m + m] = B[i];
    }

    f0.clear();
    f1.clear();
    f2.clear();
    g0.clear();
    g1.clear();
    g2.clear();
    t1.clear();
    t2.clear();
    t3.clear();
    t4.clear();
    t5.clear();
    t6.clear();
    A.clear();
    B.clear();
    C.clear();

    f0.shrink_to_fit();
    f1.shrink_to_fit();
    f2.shrink_to_fit();
    g0.shrink_to_fit();
    g1.shrink_to_fit();
    g2.shrink_to_fit();
    t1.shrink_to_fit();
    t2.shrink_to_fit();
    t3.shrink_to_fit();
    t4.shrink_to_fit();
    t5.shrink_to_fit();
    t6.shrink_to_fit();
    A.shrink_to_fit();
    B.shrink_to_fit();
    C.shrink_to_fit();

    return res;
}

vector<int> doo(int x) {
    vector<int> a;
    for (int i = 0; i < 4; i++) {
        a.push_back(x % 3);
        x /= 3;
    }
    reverse(a.begin(), a.end());
    return a;
}

int mex(int a, int b) {
    for (int i = 0; i < 3; i++) {
        if (a != i && b != i)
            return i;
    }
    return -1;
}

int main() {
    for (int i = 0; i < 81; i++) {
        vector<int> a = doo(i);
        for (int j = 0; j < 81; j++) {
            vector<int> b = doo(j);
            int x = 0;
            for (int k = 0; k < 4; k++) {
                x = x * 3 + mex(a[k], b[k]);
            }
            table[i][j] = x;
        }
    }
    int k;
    scanf("%d", &k);
    int n = 1;
    for (int i = 1; i <= k; i++)
        n *= 3;
    vector<ll> a(n), b(n);
    for (int i = 0; i < n; i++)
        scanf("%lld", &a[i]);
    for (int i = 0; i < n; i++)
        scanf("%lld", &b[i]);
    vector<ll> c = dq(a, b);
    for (int i = 0; i < n; i++)
        printf("%lld%c", c[i], " \n"[i == n - 1]);
    return 0;
}
