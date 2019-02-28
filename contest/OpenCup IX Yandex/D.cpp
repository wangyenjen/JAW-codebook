#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

namespace magic {

char s[1000001];
bool plus[1000000];
bool mul [1000000];
bool need[1000000];

bool can_remove(int i, int j) {
    if (!plus[i] && !mul[i])
        return true;

    if (!plus[i])
        return (i == 0 || s[i - 1] != '/');
    
    return (i == 0 || s[i - 1] == '+' || s[i - 1] == '(') &&
            (s[j + 1] == '\0' || s[j + 1] == '+' ||
             s[j + 1] == '-' || s[j + 1] == ')');
}

void solve() {
    vector<int> v;

    int n = strlen(s);
    fill_n(plus, n, false);
    fill_n(mul,  n, false);
    fill_n(need, n, true);

    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            v.push_back(i);
        } else if (s[i] == ')') {
            int b = v.back();
            v.pop_back();
            if (can_remove(b, i)) {
                need[b] = false;
                need[i] = false;
                if (!v.empty()) {
                    plus[v.back()] |= plus[b];
                    mul [v.back()] |= mul [b];
                }
            }
        } else if (!v.empty()) {
            if (s[i] == '+' || s[i] == '-') {
                plus[v.back()] = true;
            } else if (s[i] == '*' || s[i] == '/') {
                mul[v.back()] = true;
            }
        }
    }

    for (int i = 0; i < n; i++)
        if (need[i])
            putchar(s[i]);
    putchar('\n');
}
}

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        scanf("%1000000s", magic::s);
        magic::solve();
    }
}
