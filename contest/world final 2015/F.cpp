#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 50 + 7;
const int MAX_M = 10000 + 7;
const int INF = 0x3f3f3f3f;

const int DX[4] = {-1, 1, 0, 0};
const int DY[4] = {0, 0, -1, 1};

int r, c;
string A[MAX_N];
int dp[MAX_N][MAX_N][MAX_M];
pair<int, int> go[MAX_N][MAX_N][4];

bool in_range(int x, int y) {
    return 0 <= x && x < r && 0 <= y && y < c;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> r >> c;
    for (int i = 0; i < r; i++)
        cin >> A[i];
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            for (int k = 0; k < 4; k++)
                go[i][j][k] = make_pair(-1, -1);
            for (int k = 0; k < 4; k++) {
                int x = i, y = j;
                while (1) {
                    if (!in_range(x, y))
                        break;
                    if (A[x][y] != A[i][j])
                        break;
                    x += DX[k];
                    y += DY[k];
                }
                if (in_range(x, y))
                    go[i][j][k] = make_pair(x, y);
            }
        }
    }
    string obj;
    cin >> obj;
    obj += (char)('*');
    memset(dp, 0x3f, sizeof(dp));
    queue<tuple<int, int, int> > que;
    dp[0][0][0] = 0;
    que.emplace(0, 0, 0);
    while (!que.empty()) {
        int x, y, l;
        tie(x, y, l) = que.front();
        que.pop();
        if (l < (int)obj.size() && A[x][y] == obj[l]) {
            if (dp[x][y][l + 1] > dp[x][y][l] + 1) {
                dp[x][y][l + 1] = dp[x][y][l] + 1;
                que.emplace(x, y, l + 1);
            }
        }
        for (int i = 0; i < 4; i++) {
            int nx, ny;
            tie(nx, ny) = go[x][y][i];
            if (!in_range(nx, ny))
                continue;
            if (dp[nx][ny][l] > dp[x][y][l] + 1) {
                dp[nx][ny][l] = dp[x][y][l] + 1;
                que.emplace(nx, ny, l);
            }
        }
    }
    int ans = INF;
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            ans = min(ans, dp[i][j][(int)obj.size()]);
    printf("%d\n", ans);
    return 0;
}
