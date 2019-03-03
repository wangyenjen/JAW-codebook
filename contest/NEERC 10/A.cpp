#include <bits/stdc++.h>

using namespace std;

int main() {
    freopen("alignment.in", "r", stdin);
    freopen("alignment.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<vector<string> > vs;
    string s;
    int mx = 0;
    while (getline(cin, s)) {
        stringstream ss(s);
        string t;
        vector<string> v;
        while (ss >> t)
            v.push_back(t);
        vs.push_back(v);
        mx = max(mx, (int)v.size());
    }
    vector<int> len(mx + 1, 0);
    for (int i = 0; i < mx; i++) {
        for (int j = 0; j < (int)vs.size(); j++) {
            if (i < (int)vs[j].size())
                len[i] = max(len[i], (int)vs[j][i].size());
        }
    }
    for (int i = 0; i < (int)vs.size(); i++) {
        for (int j = 0; j < (int)vs[i].size(); j++) {
            if (j)
                cout << ' ';
            cout << vs[i][j];
            if (j == (int)vs[i].size() - 1)
                cout << '\n';
            else {
                for (int k = 0; k < len[j] - (int)vs[i][j].size(); k++)
                    cout << ' ';
            }
        }
    }
    return 0;
}
