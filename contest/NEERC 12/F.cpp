#include <bits/stdc++.h>

using namespace std;

const int DX[6] = {-1, 1, 0, 0, 0, 0};
const int DY[6] = {0, 0, -1, 1, 0, 0};
const int DZ[6] = {0, 0, 0, 0, -1, 1};

struct Pos {
    int x, y, z;

    Pos(int _x = 0, int _y = 0, int _z = 0) : x(_x), y(_y), z(_z) {}
};

int QQ[27];
char OAO[7][7][7];

bool dfs(Pos p, int dir, vector<Pos> &path) {
    static bool vis[3][3][3] = {0};
    vis[p.x][p.y][p.z] = 1;
    path.push_back(p);
    if ((int)path.size() == 27) {
        int cnt = 0;
        for (Pos pp : path) {
            if (cnt % 2 == 0) {
                OAO[pp.x][pp.y][pp.z] = (cnt / 2) + 'A';
            }
            else {
                OAO[pp.x][pp.y][pp.z] = (cnt / 2) + 'a';
            }
            cnt++;
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    cout << OAO[i][j][k];
                }
                if (j < 2) 
                    cout << " ";
            }
            cout << '\n';
        }
        return 1;
    }
    else {
        for (int i = 0; i < 6; i++) {
            int t = (int)path.size() - 1;
            if(t == 0);
            else{
                if(QQ[t] == 1 && dir != i)
                    continue;
                if(QQ[t] == 2 && (dir == i || dir == (i^1)))
                    continue;
            }
            Pos p2 = p;
            p2.x += DX[i];
            p2.y += DY[i];
            p2.z += DZ[i];
            if (p2.x < 0 || p2.x >= 3)
                continue;
            if (p2.y < 0 || p2.y >= 3)
                continue;
            if (p2.z < 0 || p2.z >= 3)
                continue;
            if (vis[p2.x][p2.y][p2.z])
                continue;
            if (dfs(p2, i, path))
                return 1;
        }
    }
    path.pop_back();
    vis[p.x][p.y][p.z] = 0;
    return 0;
}

pair<int, int> A[27];

char mp[15 + 7];

int main() {
    freopen("folding.in", "r", stdin);
    freopen("folding.out", "w", stdout);
    for (int i = 0; i < 15; i++){ 
        scanf("%s", mp);
        for(int j = 0; j < 15; j++){
            if (mp[j] >= 'A' && mp[j] <= 'N')
                A[2 * (mp[j] - 'A')] = make_pair(i, j);
            else if (mp[j] != '.')
                A[2 * (mp[j] - 'a') + 1] = make_pair(i, j);
        }
    }
    for(int i = 1; i < 26; i++){
        if(A[i - 1].first + A[i + 1].first == 2 * A[i].first && A[i - 1].second + A[i + 1].second == 2 * A[i].second)
            QQ[i] = 1;
        else
            QQ[i] = 2;
    }

    vector<Pos> path;
    if(!dfs(Pos(0, 0, 0), -1, path) && !dfs(Pos(1, 0, 0), -1, path) && !dfs(Pos(1, 1, 0), -1, path) && !dfs(Pos(1, 1, 1), -1, path));
    return 0;
}
