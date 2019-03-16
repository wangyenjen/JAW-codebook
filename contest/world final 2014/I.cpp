#include <bits/stdc++.h>

using namespace std;

struct MaxClique {
    const static int N = 111;
    typedef bitset<N> Int;
    Int linkto[N], v[N];
    int n;

    void init(int _n) {
        n = _n;
        for (int i = 0; i < n; i++) {
            linkto[i].reset();
            v[i].reset();
        }
    }

    void add_edge(int a, int b) {
        v[a][b] = v[b][a] = 1;
    }

    int popcount(const Int &val)  {
        return val.count();
    }

    int lowbit(const Int &val) {
        return val._Find_first();
    }

    int ans, stk[N];
    int id[N], di[N], deg[N];
    Int cans;

    void maxclique(int elem_num, Int candi) {
        if (elem_num > ans) {
            ans = elem_num;
            cans.reset();
            for (int i = 0; i < elem_num; i++)
                cans[id[stk[i]]] = 1;
        }
        int potential = elem_num + popcount(candi);
        if (potential <= ans)
            return;
        int pivot = lowbit(candi);
        Int smaller_candi = candi & (~linkto[pivot]);
        while (smaller_candi.count() && potential > ans) {
            int next = lowbit(smaller_candi);
            candi[next] = !candi[next];
            smaller_candi[next] = !smaller_candi[next];
            potential--;
            if (next == pivot || (smaller_candi & linkto[next]).count()) {
                stk[elem_num] = next;
                maxclique(elem_num + 1, candi & linkto[next]);
            }
        }
    }

    int solve() {
        for (int i = 0; i < n; i++) {
            id[i] = i;
            deg[i] = v[i].count();
        }

        sort(id, id + n, [&](int id1, int id2) {
            return deg[id1] > deg[id2];
        });

        for (int i = 0; i < n; i++) {
            di[id[i]] = i;
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (v[i][j])
                    linkto[di[i]][di[j]] = 1;
            }
        }

        Int cand;
        cand.reset();
        for (int i = 0; i < n; i++)
            cand[i] = 1;
        ans = 1;
        cans.reset();
        cans[0] = 1;
        maxclique(0, cand);
        return ans;
    }
} solver;

const int MAX_N= 100 + 7;

int X[MAX_N], Y[MAX_N];

int sqr(int x) {
    return x * x;
}

int dist2(int a, int b) {
    return sqr((X[a] - X[b])) + sqr((Y[a] - Y[b]));
}

int main() {
    int n, d;
    scanf("%d%d", &n, &d);
    solver.init(n);
    for (int i = 0; i < n; i++) 
        scanf("%d%d", &X[i], &Y[i]);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (dist2(i, j) <= d * d)
                solver.add_edge(i, j);
        }
    }
    int ans = solver.solve();
    printf("%d\n", ans);
    for (int i = 0, j = 0; i < n; i++) {
        if (solver.cans[i]) {
            printf("%d", i + 1);
            j++;
            if (j == ans)
                puts("");
            else
                putchar(' ');
        }
    }
    return 0;
}
