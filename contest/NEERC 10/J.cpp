#include <bits/stdc++.h>

using namespace std;

typedef double Type;
typedef pair<Type, Type> Pt;
typedef pair<Pt, Pt> Line;

#define x first
#define y second

const Type EPS = 1e-8;

Pt operator + (Pt a, Pt b) {
    return {a.x + b.x, a.y + b.y};
}

Pt operator - (Pt a, Pt b) {
    return {a.x - b.x, a.y - b.y};
}

Pt operator * (Pt a, double b) {
    return {a.x * b, a.y * b};
}

Pt operator / (Pt a, double b) {
    return {a.x / b, a.y / b};
}

Type operator * (Pt a, Pt b) {
    return a.x * b.x + a.y * b.y;
}

Type operator ^ (Pt a, Pt b) {
    return a.x * b.y - a.y * b.x;
}

Pt perp(Pt a) {
    return {a.y, -a.x};
}

Type len(Pt a) {
    return sqrt(a * a);
}

Pt interPnt(Line l1, Line l2, bool &res) {
    Pt p1, p2, q1, q2;
    tie(p1, p2) = l1;
    tie(q1, q2) = l2;
    double f1 = (p2 - p1) ^ (q1 - p1);
    double f2 = (p2 - p1) ^ (p1 - q2);
    double f = f1 + f2;
    if (fabs(f) < EPS) {
        res = 0;
        return {0, 0};
    }
    res = 1;
    return q1 * (f2 / f) + q2 * (f1 / f);
}

bool isin(Line l0, Line l1, Line l2) {
    bool res;
    Pt p = interPnt(l1, l2, res);
    return ((l0.second - l0.first) ^ (p - l0.first)) > EPS;
}

vector<Line> half(vector<Line> lines) {
    int sz = (int)lines.size();
    vector<double> ata(sz), ord(sz);
    for (int i = 0; i < sz; i++) {
        ord[i] = i;
        Pt d = lines[i].second - lines[i].first;
        ata[i] = atan2(d.y, d.x);
    }
    sort(ord.begin(), ord.end(), [&](int i, int j) {
        if (fabs(ata[i] - ata[j]) < EPS)  {
            return ((lines[i].second - lines[i].first) ^ (lines[j].second - lines[i].first)) < 0;
        }       
        return ata[i] < ata[j];
    });
    vector<Line> fin;
    for (int i = 0; i < sz; i++) {
        if (!i or fabs(ata[ord[i]] - ata[ord[i - 1]]) > EPS)
            fin.push_back(lines[ord[i]]);
    }
    deque<Line> dq;
    for (int i = 0; i < (int)fin.size(); i++) {
        while ((int)dq.size() >= 2 and
            not isin(fin[i], dq[(int)dq.size() - 2], dq[(int)dq.size() - 1]))
            dq.pop_back();
        while ((int)dq.size() >= 2 and 
            not isin(fin[i], dq[0], dq[1]))
            dq.pop_front();
        dq.push_back(fin[i]);
    }
    while ((int)dq.size() >= 3 and
        not isin(dq[0], dq[(int)dq.size() - 2], dq.back()))
        dq.pop_back();
    while ((int)dq.size() >= 3 and 
        not isin(dq.back(), dq[0], dq[1]))
        dq.pop_front();
    vector<Line> res(dq.begin(), dq.end());
    return res;
}

int n;
vector<Pt> ps;

int check(int x) {
    vector<Line> vs;
    for (int i = 0; i < n; i++) {
        int j = (i + x + 1) % n;
        vs.emplace_back(ps[j], ps[i]);
        vs.emplace_back(ps[i], ps[(i + n - 1) % n]);
    }
#if 0
    printf("\n\nmeow %d\n", x);
    printf("(%.5f, %.5f), (%.5f, %.5f)\n", half(vs)[0].first.x, half(vs)[0].first.y, half(vs)[0].second.x, half(vs)[0].second.y);
    printf("(%.5f, %.5f), (%.5f, %.5f)\n", half(vs)[1].first.x, half(vs)[1].first.y, half(vs)[1].second.x, half(vs)[1].second.y);
#endif
    return half(vs).size() >= 3;
}

int main() {
    freopen("jungle.in", "r", stdin);
    freopen("jungle.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        double x, y;
        scanf("%lf%lf", &x, &y);
        ps.emplace_back(x, y);
    }
    int lb = 1, rb = n - 2;
    while (lb < rb) {
        int mid = (lb + rb) / 2;
        if (check(mid))
            lb = mid + 1;
        else
            rb = mid;
    }
    printf("%d\n", lb);
    return 0;
}
