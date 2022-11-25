const int MAX_N = 200000 + 7;
const int MAX_LOG_N = 20 + 1;

template <typename T>
struct SparseTable {
  int log_table[MAX_N];
  T dp[MAX_LOG_N][MAX_N];

  void init(int n, T A[]) {
    log_table[0] = -1;
    for (int i = 1; i <= n; i++) {
        log_table[i] = log_table[i >> 1] + 1;
    }

    for (int i = 0; i <= n; i++) {
        dp[0][i] = A[i];
    }
    for (int i = 1; (1 << i) <= n; i++) {
        for (int j = 0; j + (1 << i) <= n; j++) {
          dp[i][j] = min(dp[i - 1][j], dp[i - 1][j + (1 << (i - 1))]);
        }
    }
  }

  SparseTable() {}
  SparseTable(int n, T A[]) {
    init(n, A);
  }

  T query(int l, int r) {
    int t = log_table[r - l + 1];
    return min(dp[t][l], dp[t][r - (1 << t) + 1]);
  }
};

