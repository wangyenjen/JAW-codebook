#include<bits/stdc++.h>
using namespace std;
#define ll long long int

const int N = 10007;
bool prime[N + 87];
vector<pair<int, ll> > primes;

bool isprime(int p){
    if(p <= N)
        return prime[p];
    for(int i = 2; i <= N; i++)
        if(prime[i] && (p % i == 0))
            return false;
    return true;
}

ll func(int k, int p){
    ll ans = 0;
    while(k > 0){
        ans += k / p;
        k /= p;
    }
    return ans;
}

int main(){
    freopen("factorial.in", "r", stdin);
    freopen("factorial.out", "w", stdout);
    for(int i = 2; i <= N; i++)
        prime[i] = true;
    for(int i = 2; i <= N; i++)
        if(prime[i]){
            primes.emplace_back(i, 0);
            for(int j = i; i * j <= N; j++)
                prime[i * j] = false;
        }
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n + m; i++){
        int tmp;
        scanf("%d", &tmp);
        for(int t = 0; t < (int)primes.size(); t++){
            primes[t].second += (i < n ? 1ll : -1ll) * func(tmp, primes[t].first);
        }
    }

    //-1
    for(auto p : primes){
        if(p.second < 0){
            printf("-1\n");
            return 0;
        }
    }

    vector<pair<int, ll> > ans;
    for(int i = N; i >= 2; i--){
        vector<pair<int, ll> >V;
        ll cnt = -1;
        for(auto p : primes){
            V.emplace_back(p.first, func(i, p.first));
            ll tmp = V.back().second;
            if(tmp > 0){
                if(cnt == -1)
                    cnt = p.second / V.back().second;
                cnt = min(cnt, p.second / V.back().second);
            }
        }
        if(cnt > 0){
            ans.emplace_back(i, cnt);
            for(int i = 0; i < (int)primes.size(); i++)
                primes[i].second -= cnt * V[i].second;
        }
    }

    if(ans.empty())
        printf("0\n");
    else{
        printf("%d\n", (int)ans.size());
        for(auto p : ans)
            printf("%d %lld\n", p.first, p.second);
    }
}
