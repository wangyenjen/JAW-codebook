#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define MOD 998244353

const int N = 2000;
int n;
int A[2][11];
ll fac[N + 87];

ll dp[N + 87][11], dp1[N + 87][11];
void make1(){
	vector<int>V;
	for(int i = 0; i < 11; i++)
		for(int j = 0; j < A[1][i]; j++)
			V.push_back(i);
	int m = (int)V.size();
	for(int i = 0; i <= m; i++)
		for(int j = 0; j < 11; j++)
			dp[i][j] = 0;
	dp[0][0] = 1;

	for(auto p : V){
		for(int i = 0; i <= m; i++)
			for(int j = 0; j < 11; j++)
				dp1[i][j] = dp[i][j];
		for(int i = 0; i < m; i++)
			for(int j = 0; j < 11; j++){
				dp1[i + 1][(j + p) % 11] += dp[i][j];
				if(dp1[i + 1][(j + p) % 11] >= MOD)
					dp1[i + 1][(j + p) % 11] -= MOD;
			}
		swap(dp, dp1);
	}

	swap(dp, dp1);
	for(int i = 0; i <= n + 1; i++)
		for(int j = 0; j < 11; j++)
			dp[i][j] = 0;
	int s = 0;
	for(auto p : V)
		s = (s + p) % 11;
	for(int j = 0; j < 11; j++){
		dp[m / 2 + 1][(s - 2 * j + 22) % 11] = dp1[m / 2][j] * fac[m / 2] % MOD * fac[m - m / 2] % MOD;
	}
}

void make2(){
	vector<int>V;
	for(int j = 0; j < 11; j++){
		for(int i = 0; i < A[0][j]; i++)
			V.push_back(j);
	}
	int S = n - (int)V.size();
	for(auto p : V){
		S++;
		for(int i = 0; i <= n + 1; i++)
			for(int j = 0; j < 11; j++)
				dp1[i][j] = 0;
		for(int i = 0; i <= n + 1; i++)
			for(int j = 0; j < 11; j++){
				if(i <= n)
                    dp1[i + 1][(j + p) % 11] = (dp1[i + 1][(j + p) % 11] + dp[i][j] * i) % MOD;
				dp1[i][(j - p + 11) % 11] = (dp1[i][(j - p + 11) % 11] + dp[i][j] * (S - i)) % MOD;
			}
		swap(dp, dp1);
	}
	ll ans = 0;
	for(int i = 0; i <= n + 1; i++){
		ans = ans + dp[i][0];
		if(ans >= MOD)
			ans -= MOD;
	}
	printf("%lld\n", ans);
}

int main(){
	fac[0] = 1;
	for(int i = 1; i <= N; i++)
		fac[i] = fac[i - 1] * i % MOD;
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for(int i = 0; i < 2; i++)
            for(int j = 0; j < 11; j++)
                A[i][j] = 0;
        for(int i = 0; i < n; i++){
            int tmp;
            scanf("%d", &tmp);
            int a = tmp % 11, b = 0;
            while(tmp > 0){
                tmp /= 10;
                b ^= 1;
            }
            A[b][a]++;
        }
        make1();
        make2();
    }
    return 0;
}
