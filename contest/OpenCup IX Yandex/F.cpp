#pragma GCC optimize "O3"
#include <cstdio>
#include <bitset>
#include <algorithm>
using namespace std;

const int MAX_N = 250;

struct MaxClique {
	static const int N = 250;
	typedef bitset<N> Int;
	Int linkto[N], v[N];
	int n;

	void init(int _n) {
		n = _n;
		for (int i = 0; i < n; i++) {
			linkto[i].reset();
			v[i].reset();
		}
	}

	void add_edge(int a, int b) {
		v[a][b] = v[b][a] = 1;
	}

	int popcount(const Int &val) {
		return val.count();
	}

	int lowbit(const Int &val) {
		return val._Find_first();
	}

	int ans, ans_cnt;
	int id[N], di[N], deg[N];

	void maxclique(int elem_num, Int candi) {
		// fprintf(stderr, "elem_num %d\n", elem_num);
		if (elem_num > ans) {
			ans = elem_num;
			ans_cnt = 1;
		} else if (elem_num == ans) {
			ans_cnt++;
		}

		int potential = elem_num + popcount(candi);
		if (potential < ans)
			return;

#if 0
		while (candi.any() && potential >= ans) {
			int next = lowbit(candi);
			candi[next] = false;
			potential--;

			maxclique(elem_num + 1, candi & linkto[next]);
		}

#else
		int pivot = lowbit(candi);
		Int smaller_candi = candi & (~linkto[pivot]);
		while (smaller_candi.any() && potential >= ans) {
			int next = lowbit(smaller_candi);
			candi[next] = !candi[next];
			smaller_candi[next] = !smaller_candi[next];
			potential--;
			// if (next == pivot || (smaller_candi & linkto[next]).any()) {
				maxclique(elem_num + 1, candi & linkto[next]);
			// }
		}
#endif
	}

	pair<int, int> solve() {
		for (int i = 0; i < n; i++) {
			id[i] = i;
			deg[i] = v[i].count();
		}
		sort(id, id + n, [&](int id1, int id2) {return deg[id1] > deg[id2];});
		for (int i = 0; i < n; i++) 
			di[id[i]] = i;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (v[i][j])
					linkto[di[i]][di[j]] = 1;
			}
		}
		Int cand;
		cand.reset();
		for (int i = 0; i < n; i++)
			cand[i] = 1;
		ans = 1;
		ans_cnt = 0;
		maxclique(0, cand);
		return make_pair(ans, ans_cnt);
	}
} solver;


struct Dsu {
	int n;
	int par[MAX_N], sz[MAX_N];

	void init(int _n) {
		n = _n;
		for (int i = 0; i < n; i++) {
			par[i] = i;
			sz[i] = 1;
		}
	}

	int find(int x) {
		if (x == par[x])
			return x;
		else
			return par[x] = find(par[x]);
	}

	bool merge(int x, int y) {
		x = find(x);
		y = find(y);
		if (x == y)
			return 0;
		if (sz[x] < sz[y])
			swap(x, y);
		sz[x] += sz[y];
		par[y] = x;
		return 1;
	}
} dsu;

bitset<250> adj[250];
int minc[250];
bool enemy[250][250];
int map[250];

int main() {
	int n, p, q;
	scanf("%d%d%d", &n, &p, &q);
	for (int i = 0; i < p; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		a--, b--;

		adj[a][b] = adj[b][a] = true;
	}

	for (int i = 0; i < n; i++)
		adj[i][i] = true;
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			if (adj[i][k])
				adj[i] |= adj[k];

	for (int i = 0; i < n; i++) {
		minc[i] = i;
		for (int j = 0; j < i; j++)
			if (adj[i][j]) {
				minc[i] = j;
				break;
			}
	}

	for (int i = 0; i < q; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		a--, b--;
		a = minc[a];
		b = minc[b];
		enemy[a][b] = enemy[b][a] = true;
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			enemy[i][j] = enemy[minc[i]][minc[j]];
	
	int nn = 0;
	for (int i = 0; i < n; i++)
		if (!enemy[i][i])
			map[i] = nn++;

	if (nn == 0) {
		puts("0 1");
		return 0;
	}

	solver.init(nn);

	// printf("nn=%d\n", nn);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i != j && !enemy[i][i] && !enemy[j][j] && !enemy[i][j]) {
				solver.add_edge(map[i], map[j]);
				// printf("%d--%d\n", map[i], map[j]);
			}

	auto pa = solver.solve();

	printf("%d %d\n", pa.first, pa.second);
}
