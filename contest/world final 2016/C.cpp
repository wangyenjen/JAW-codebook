#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 50 + 7;

int A[MAX_N];
bool ban[MAX_N];
int nxt[MAX_N][MAX_N][2];

void insert(int id, int p, int &u) {
    if (u == -1) {
        u = p;
        return;
    }
    if (A[p] < A[u]) 
        insert(id, p, nxt[id][u][0]);
    else
        insert(id, p, nxt[id][u][1]);
}

bool check(int id1, int id2, int u1, int u2) {
    if (nxt[id1][u1][0] == -1) {
        if (nxt[id2][u2][0] != -1)
            return 0;
    }
    else {
        if (nxt[id2][u2][0] == -1)
            return 0;
        if (!check(id1, id2, nxt[id1][u1][0], nxt[id2][u2][0]))
            return 0;
    }
    
    if (nxt[id1][u1][1] == -1) {
        if (nxt[id2][u2][1] != -1)
            return 0;
    }
    else {
        if (nxt[id2][u2][1] == -1)
            return 0;
        if (!check(id1, id2, nxt[id1][u1][1], nxt[id2][u2][1]))
            return 0;
    }

    return 1;
}

int main() {
    memset(nxt, -1, sizeof(nxt));
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++)
            scanf("%d", &A[j]);
        for (int j = 1; j < k; j++) {
            int root = 0;
            insert(i, j, root);
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (ban[i])
            continue;
        ans++;
        for (int j = i + 1; j < n; j++) {
            if (check(i, j, 0, 0)) 
                ban[j] = 1;
        }
    }
    printf("%d\n", ans);
    return 0;
}
