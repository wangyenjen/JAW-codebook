#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;

template<typename Node>
double dist(const Node &l, const Node &r) {
    return hypot(l.x - r.x, l.y - r.y);
}

struct Node {
    int x, y;
    double d;

    void read() {
        scanf("%d%d", &x, &y);
    }
};


void read_path(vector<Node> &path) {
    int n;
    scanf("%d", &n);
    path.resize(n);
    for (int i = 0; i < n; i++)
        path[i].read();

    path[0].d = 0;
    for (int i = 1; i < n; i++)
        path[i].d = path[i - 1].d + dist(path[i], path[i - 1]);
}

bool check(double d, vector<Node> &path1, vector<Node> &path2) {
    int n = path1.size(), m = path2.size();
    int i = 0, j = 0;
    while (j + 1 < path[j + 1]
    // (0, d)
    
    return true;
}

int main() {
    vector<Node> path1, path2;
    read_path(path1);
    read_path(path2);

    if (dist(path1.front(), path2.back()) > path2.back().d) {
        puts("impossible");
        return 0;
    }

    double mint = 0, maxt = dist(path1.front(), path2.back());
    for (int rep = 0; rep < 64; rep++) {
        double mid = (mint + maxt) / 2;
        (check(mid, path1, path2) ? maxt : mint) = mid;
    }
    printf("%.9f\n", mint);
}
