#include <cstdio>
#include <algorithm>
using namespace std;

bool bit[202][202];
int vis[202][202];
int cnt[40000];
char ans[40001];

int hex2int(char c) {
    if ('0' <= c && c <= '9')
        return c - '0';
    return c - 'a' + 10;
}

void dfs1(int i, int j, int cc) {
    if (!bit[i][j] || vis[i][j] >= 0)
        return;
    vis[i][j] = cc;
    dfs1(i + 1, j, cc);
    dfs1(i - 1, j, cc);
    dfs1(i, j + 1, cc);
    dfs1(i, j - 1, cc);
}
void dfs2(int i, int j, int h, int w) {
    if (i < 0 || j < 0 || i >= h || j >= w || vis[i][j] >= 0)
        return;
    vis[i][j] = 0;
    dfs2(i + 1, j, h, w);
    dfs2(i - 1, j, h, w);
    dfs2(i, j + 1, h, w);
    dfs2(i, j - 1, h, w);
}
void dfs3(int i, int j, bool &done) {
    if (bit[i][j] && !done) {
        cnt[vis[i][j]]++;
        done = true;
    }
    if (vis[i][j] >= 0)
        return;
    vis[i][j] = 0;
    dfs3(i + 1, j, done);
    dfs3(i - 1, j, done);
    dfs3(i, j + 1, done);
    dfs3(i, j - 1, done);
}

void solve(int h, int w, int test) {
    fill_n(bit[0], w * 4 + 2, false);
    for (int i = 1; i <= h; i++) {
        bit[i][0] = false;
        char s[51];
        scanf("%50s", s);

        for (int j = 0; j < w; j++) {
            int x = hex2int(s[j]);
            for (int k = 0; k < 4; k++)
                bit[i][j * 4 + k + 1] = x & (1 << (3 - k));
        }
        bit[i][4 * w + 1] = false;
    }
    fill_n(bit[h + 1], w * 4 + 2, false);

    h += 2;
    w = w * 4 + 2;

    // for (int i = 0; i < h; i++) {
    //     for (int j = 0; j < w; j++)
    //         putchar(bit[i][j] ? '1' : '0');
    //     putchar('\n');
    // }

    for (int i = 0; i < h; i++)
        fill_n(vis[i], w, -1);
    
    int nc = 0;
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            if (bit[i][j] && vis[i][j] < 0)
                dfs1(i, j, nc++);
    dfs2(0, 0, h, w);

    fill_n(cnt, nc, 0);
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            if (vis[i][j] < 0) {
                bool done = false;
                dfs3(i, j, done);
            }
    for (int i = 0; i < nc; i++)
        ans[i] = "WAKJSD"[cnt[i]];
    ans[nc] = '\0';
    sort(ans, ans + nc);
    printf("Case %d: %s\n", test, ans);
}
int main() {
    for (int t = 1, h, w; scanf("%d%d", &h, &w), h; t++) {
        solve(h, w, t);
    }
}
