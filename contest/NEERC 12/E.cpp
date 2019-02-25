#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

long long q[100000];

struct Cmp {
    bool operator () (int l, int r) const {
        return q[l] < q[r];
    }
};

vector<int> boxes[19];

int main() {
#ifndef JOHNCHEN902
    freopen("exact.in", "r", stdin);
    freopen("exact.out", "w", stdout);
#endif
    long long x;
    int n;
    scanf("%lld%d", &x, &n);

    for (int i = 0; i < n; i++) {
        int k;
        scanf("%d%lld", &k, q + i);

        for (int j = 0; j < k; j++)
            q[i] *= 10;

        boxes[k].push_back(i);
    }

    vector<int> ans;
    vector<int> v;
    long long sumans = 0;

    long long pow10 = 1;
    for (int k = 0; k <= 18; k++) {
        sort(boxes[k].begin(), boxes[k].end(), Cmp());
        vector<int> w(v.size() + boxes[k].size());
        merge(v.begin(), v.end(), boxes[k].begin(), boxes[k].end(), w.begin(), Cmp());
        v = move(w);

        while (sumans < (k == 18 ? x : x % (pow10 * 10))) {
            if (v.empty()) {
                puts("-1");
                return 0;
            }

            sumans += q[v.back()];
            ans.push_back(v.back());

            v.pop_back();
        }

        if (k < 18)
            pow10 *= 10;
    }

    printf("%zd\n", ans.size());
    for (int i = 0; i < (int) ans.size(); i++)
        printf("%d%c", ans[i] + 1, i == (int) ans.size() - 1 ? '\n' : ' ');
}
