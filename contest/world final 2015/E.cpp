#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
using namespace std;

bool is_subseq_of(const string &l, const string &r) {
    for (int i = 0, j = 0; i < (int) l.size(); i++, j++) {
        while (j < (int) r.size() && l[i] != r[j])
            j++;
        if (j >= (int) r.size())
            return false;
    }
    return true;
}

string s[4001];
vector<int> v[4001]; // sorted increasingly
int which[4001];

bool solve(int n) {
    if (!is_subseq_of(s[1], s[0]))
        return false;

    v[1] = {0};
    for (int i = 2; i <= n; i++) {
        vector<int> &v2 = v[i];
        if (is_subseq_of(s[i], s[i - 1]))
            v2 = v[i - 1];

        for (int j : v[i - 1])
            if (is_subseq_of(s[i], s[j])) {
                which[i] = j;
                v2.push_back(i - 1);
                break;
            }

        if (v2.empty())
            return false;

        for (int j = (int) v2.size() - 1; j >= 0; j--)
            for (int k = 0; k < j; k++)
                if (is_subseq_of(s[v2[j]], s[v2[k]])) {
                    v2.erase(v2.begin() + j);
                    break;
                }
        assert(v2.size() <= 2);
    }

    vector<int> va, vb;
    int a = n, b = v[n][0];
    for (int i = n; i >= 1; i--) {
        if (i != a) {
            swap(a, b);
            swap(va, vb);
        }
        assert(i == a);
        va.push_back(i);

        if (b != a - 1) {
            a = a - 1;
        } else {
            a = which[a];
        }
    }

    printf("%zd %zd\n", va.size(), vb.size());
    for (int i = 0; i < (int) va.size(); i++)
        puts(s[va[i]].c_str());
    for (int i = 0; i < (int) vb.size(); i++)
        puts(s[vb[i]].c_str());
    return true;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i <= n; i++) {
        char buf[4001];
        scanf("%4000s", buf);
        s[i] = buf;
    }

    sort(s + 1, s + n + 1,
        [](const string &l, const string &r) {
            return l.size() > r.size();
        });

    if (!solve(n))
        puts("impossible");
}
