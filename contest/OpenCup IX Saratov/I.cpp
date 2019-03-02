#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1000 + 7;
const double PI = acos(-1.0);

int n, d;
int X[MAX_N], Y[MAX_N];

vector<pair<double, int> > es;

pair<double, double> adjust(double lb, double rb) {
    while (lb < 0) {
        lb += 2 * PI;
        rb += 2 * PI;
    }
    while (lb > 2 * PI) {
        lb -= 2 * PI;
        rb -= 2 * PI;        
    }

    if(rb > 2 * PI){
        es.emplace_back(lb, -1);
        es.emplace_back(2 * PI, 1);
        es.emplace_back(0, -1);
        es.emplace_back(rb - 2 * PI, 1);
    }
    else{
        es.emplace_back(lb, -1);
        es.emplace_back(rb, 1);
    }

    return make_pair(lb, rb);
}

int calc(int id) {
    es.clear();
    for (int i = 1; i <= n; i++) {
        if (i == id)
            continue;
        double x = X[i] - X[id];
        double y = Y[i] - Y[id];
        double r = sqrt(x * x + y * y);
        double theta = atan2(y, x);
        if (d < r) {
            double lb = theta + acos(d / r);
            double rb = theta + PI / 2;
            tie(lb, rb) = adjust(lb, rb);
       
            lb = theta - PI / 2;
            rb = theta - acos(d / r);
            tie(lb, rb) = adjust(lb, rb);
        }
        else {
            double lb = theta - PI / 2;
            double rb = theta + PI / 2;
            tie(lb, rb) = adjust(lb, rb);
        }
    }

    sort(es.begin(), es.end());
    int ans = 1;
    int s = 0;
    // printf("\n\n haha (%d, %d)\n", X[id], Y[id]);
    for (pair<double, int> p : es) {
        // printf("%.10f %d\n", p.first, p.second);
        s -= p.second;
        ans = max(ans, s + 1);
    }
    return ans;
}

int main() {
    freopen("statistics.in", "r", stdin);

    scanf("%d%d", &n, &d);
    d *= 2;
    for (int i = 1; i <= n; i++) 
        scanf("%d%d", &X[i], &Y[i]);
    
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, calc(i));

    printf("%d\n", ans);

    return 0;
}
