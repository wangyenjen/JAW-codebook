#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;

constexpr int inf = 1000000007;

string s[100], t[100];

constexpr int zcode = 200000;
static int encode(bool rev, int i, int pos) {
    return rev * 100 * 1000 + i * 1000 + pos;
}
static tuple<bool, int, int> decode (int code) {
    return make_tuple(code < 100000, (code / 1000) % 100, code % 1000);
}

vector<int> adj[200001];
static int edgecost(int code1, int code2) {
    auto [r1, i1, p1] = decode(code1);
    auto [r2, i2, p2] = decode(code2);

    ;
}

int main() {
    freopen("palindrome.in", "r", stdin);
    // freopen("palindrome.out", "w", stdout);
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        char buf[1001];
        scanf("%1000s", buf);
        t[i] = s[i] = buf;
        reverse(t[i].begin(), t[i].end());
    }


}
