#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 10000 + 7;
int vis[MAX_N];
int iso[MAX_N];

int main() {
    int kcase = 0, n;
    while (scanf("%d", &n) == 1) {
        vector<vector<int> > vs;
        vector<int> rd;
        for (int i = 0; i < n; i++) {
            int h;
            scanf("%d", &h);
            vector<int> v;
            while (h--) {
                int x;
                scanf("%d", &x);
                v.push_back(x);
                rd.push_back(x);
            }
            vs.push_back(v);
        }
        sort(rd.begin(), rd.end());
        rd.erase(unique(rd.begin(), rd.end()), rd.end());
        int ans = n - 1;
        for(int i = 0; i <= (int)rd.size(); i++){
            vis[i] = 0;
            iso[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            for (int &x : vs[i])
                x = lower_bound(rd.begin(), rd.end(), x) - rd.begin() + 1;
            vs[i].erase(unique(vs[i].begin(), vs[i].end()), vs[i].end());
            ans += ((int)vs[i].size() - 1) * 2;
            for (int j = 0; j < (int)vs[i].size(); j++){
                if((j == 0 || vs[i][j - 1] <= vs[i][j] - 1) && (j == (int)vs[i].size() - 1 || vs[i][j + 1] > vs[i][j] + 1))
                    iso[vs[i][j]] = 1;
            }
            for (int j = 0; j + 1 < (int)vs[i].size(); j++) {
                if (vs[i][j] + 1 == vs[i][j + 1]) {
                    vis[vs[i][j]]++;
                }
            }
        }
        for (int i = 0; i < (int)rd.size() - 1; i++){
            if(i > 0 && vis[i - 1] == 1 && vis[i] == 1 && iso[i] > 0)
                vis[i - 1] = -514;
        }
        for (int i = 0; i < (int)rd.size(); i++){
            if(vis[i] >= 1)
                ans -= 2;
            else if(vis[i] == -514){
                int cnt = 0;
                while(vis[i + (++cnt)] == 2);
                ans -= ((int)(cnt + 1) / 2) * 2;
                i = i + cnt;
            }
        }
        printf("Case %d: %d\n", ++kcase, ans);
    }
    return 0;
}
