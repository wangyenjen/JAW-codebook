#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100000 + 7;

int a[MAX_N], cnt[MAX_N];
vector<int> es[MAX_N];

int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	int A = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		A += a[i];
	}
	for (int i = 0; i < k; i++) {
		int x;
		scanf("%d", &x);
		cnt[x]++;
	}
	int r = k / A;
	k %= A;
	for (int i = 1; i <= n; i++) {
		for (int j = cnt[i] - r * a[i] + 1 ; j <= a[i]; j++) {
			int lb = max(k + 1, int(1ll * (j - 1) * A / a[i]) - 1);
			int rb = min(int((1ll * j * A / a[i]) + (1ll * j * A % a[i] != 0)), A);
			if (lb <= rb)
				es[lb].push_back(rb);
		}
	}
	int ans = A;
	priority_queue<int, vector<int>, greater<int> > pq;
	for (int i = 0; i <= A; i++) {
		for (int x : es[i])
			pq.push(x);
		if (!pq.empty() && pq.top() < i) {
			ans = pq.top() - 1 - k;
			break;
		}
		if (!pq.empty()) 
			pq.pop();
	}
	if (ans >= A) 
		puts("forever");
	else
		printf("%d\n", ans);
	return 0;
}
