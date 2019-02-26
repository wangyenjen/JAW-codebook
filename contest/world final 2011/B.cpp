#include<bits/stdc++.h>
using namespace std;

int x[9], y[9];

bool isint(double p){
	return fabs(p - (int)(p + 0.2)) < 1e-6;
}

int rnd(double p){
	if(p < 0)
		return -rnd(-p);
	if(isint(p))
		return (int)(p + 0.2);
	else if(isint(2 * p))
		return (int)(2 * p + 0.6);
	else
		return (int)(p + 0.5);
}

pair<int,int> make(int a, int b, int c, int d, int e, int f){
	pair<int,int> _nul = make_pair(0, 0);
	if(d == e && e == f){
		if(a == b && b == c)
			return make_pair(0, 1);
		else return _nul;
	}
	if(d != f){
		swap(e, f);
		swap(b, c);
	}
	if(e != f){
		swap(d, f);
		swap(a, c);
	}
	if((a - b) % (d - e) != 0)
		return _nul;
	int t = (a - b) / (d - e);
	if(t == 0)
		return _nul;
	if((e - f) * t != b - c)
		return _nul;
	return make_pair(a - d * t, t);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t = 0;
	while(cin >> x[0] >> y[0] >> x[1] >> y[1] >> x[2] >> y[2]){
		t++;
		if(x[0] == 0 && y[0] == 0 && x[1] == 0 && y[1] == 0 && x[2] == 0 && y[2] == 0)
			break;
		cin >> x[3] >> y[3] >> x[4] >> y[4] >> x[5] >> y[5];
		
		vector<pair<int,int>>axis;
		for(int i = 0; i < 10; i++)
			axis.emplace_back(10, i);
		for(int i = 10; i > -10; i--)
			axis.emplace_back(i, 10);
		for(int i = 10; i > 0; i--)
			axis.emplace_back(-10, i);

		int ans = 0;
		for(auto p : axis){
			double c = 1.0 * p.first / sqrt(1.0 * p.first * p.first + 1.0 * p.second * p.second);
			double s = 1.0 * p.second / sqrt(1.0 * p.first * p.first + 1.0 * p.second * p.second);
			for(int i = 0; i < 3; i++){
				x[i + 6] = rnd(c * x[i] + s * y[i]);
				y[i + 6] = rnd(-s * x[i] + c * y[i]);
			}
			vector<pair<pair<int,int>, pair<int,int>> > T;
			const int perm[6][3] = {{3, 4, 5}, {3, 5, 4}, {4, 3, 5}, {4, 5, 3}, {5, 3, 4}, {5, 4, 3}};
			for(int i = 0; i < 6; i++){
				pair<int,int> tmp = make(x[perm[i][0]], x[perm[i][1]], x[perm[i][2]], x[6], x[7], x[8]);
				pair<int,int> tmp2 = make(y[perm[i][0]], y[perm[i][1]], y[perm[i][2]], y[6], y[7], y[8]);
				if(tmp == make_pair(0, 0) || tmp2 == make_pair(0, 0))
					continue;
				if(x[6] == x[7] && x[7] == x[8])
					ans += 878787;
				if(y[6] == y[7] && y[7] == y[8])
					ans += 878787;
				T.emplace_back(tmp, tmp2);
			}
			sort(T.begin(), T.end());
			T.erase(unique(T.begin(), T.end()), T.end());
			ans += (int)T.size();
		}
		if(ans == 0)
			cout << "Case " << t << ": no solution\n";
		else if(ans == 1)
			cout << "Case " << t << ": equivalent solutions\n";
		else
			cout << "Case " << t << ": inconsistent solutions\n";
	}
}
