/// {{{ Author: Wang, Yen-Jen
// include
#include <bits/stdc++.h>

// using
using namespace std;

// types
typedef long long ll;
typedef pair<int, int> pii;

// macro
#define SZ(x) ((int)x.size())
#define ALL(x) (x).begin(), (x).end()
#define REP(i, n) for (int i = 0; i < int(n); i++)
#define REP1(i, a, b) for (int i = a; i <= int(b); i++)
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define LC o << 1, l, m
#define RC o << 1 | 1, m + 1, r
#define MS(x, v) memset(x, (v), sizeof(x))

// input
inline bool SR(int &x) {
  return scanf("%d", &x) == 1;
}

inline bool SR(ll &x) {
  return scanf("%lld", &x) == 1;
}

inline bool SR(double &x) {
  return scanf("%lf", &x) == 1;
}

inline bool SR(char *s) {
  return scanf("%s", s) == 1;
}

inline bool RI() {
  return true;
}

template<typename I, typename... T> inline bool RI(I &x, T&... tail) {
  return SR(x) && RI(tail...);
}

// output
inline void SP(const int x) {
  printf("%d", x);
}

inline void SP(const ll x) {
  printf("%lld", x);
}

inline void SP(const double x) {
  printf("%.16lf", x);
}

inline void SP(const char *s) {
  printf("%s", s);
}

inline void PL() {
  puts("");
}

template<typename I, typename... T> inline void PL(const I x, const T... tail) {
  SP(x);
  if (sizeof...(tail)) putchar(' ');
  PL(tail...);
}

// debug
#define WangYenJen

#ifdef WangYenJen
template<typename I> void _DOING(const char *s, I&& x) {
  cerr << s << " = " << x << endl;
}

template<typename I, typename... T> void _DOING(const char *s, I&& x, T&&... tail) {
  int c = 0;
  while (*s != ',' || c != 0) {
    if (*s == '(' || *s == '[' || *s == '{') c++;
    if (*s == ')' || *s == ']' || *s == '}') c--;
    cerr << *s++;
  }
  cerr << " = " << x << ", ";
  _DOING(s + 1, tail...);
}

#define DEBUG(...) \
do { \
  fprintf(stderr, "%s: Line %d - ", __PRETTY_FUNCTION__, __LINE__); \
  _DOING(#__VA_ARGS__, __VA_ARGS__); \
} while (0);

#else
#define DEBUG(...)

#endif

// constant number
const int INF = 0x3f3f3f3f;
const ll INF64 = 0x3f3f3f3f3f3f3f3fll;

// random function
inline int RAND() {
  static int x = 880301;
  return (x = x * 0xdefaced + 1) % 0x7fffffff;
}
/// }}}

int main() {
  return 0;
}
