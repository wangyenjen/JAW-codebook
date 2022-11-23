#include <cstdint>
#include <algorithm>
 
using Long = unsigned __int128;
using Int = uint64_t;
const Int P = 9097271247288401921, G = 6;
 
inline Int Norm(Int x) {
  return x + (P & (int64_t)x >> 63);
}
 
inline Int Inv(Int b) {
  return ((Long)1 << (64 + 63 - __builtin_clzll(b))) / b;
}
 
inline Int Mod(Int a, Int b) {
  int q = 63 - __builtin_clzll(P);
  Long v = (Long)a * b;
  Int x = v >> (2 * q - 62);
  Int y = ((Long)x * Inv(P)) >> (126 - q);
  Int ans = (Int)v - y * P;
  Int rm = ans - P;
  return rm + (P & ((int64_t)rm >> 63));
}
 
inline Int PowMod(Int a, Int c) {
  Int ret = 1;
  for (; c; c >>= 1, a = Mod(a, a)) {
    if (c & 1) ret = Mod(ret, a);
  }
  return ret;
}
 
void NTTBuildWs(Int ws[], size_t N) {
  ws[0] = 1;
  Int w1 = PowMod(G, (P - 1) / N);
  for (size_t i = 1; i < N / 2; i++) ws[i] = Mod(ws[i - 1], w1);
}
 
void NTT(Int D[], Int tmp[], Int ws[], size_t N, bool loc = false, size_t st = 1) {
  if (N == 2) {
    Int* y = loc ? tmp : D;
    for (size_t i = 0; i < st; i++) {
      Int a = D[i], b = D[i + st];
      y[i] = Norm(a + b - P); y[i + st] = Norm(a - b);
    }
  }
  if (N <= 2) return;
  N >>= 1;
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < st; j++) {
      Int a = D[st * i + j], b = D[st * (i + N) + j];
      tmp[2*i*st + j] = Norm(a + b - P);
      tmp[(2*i+1)*st + j] = Mod(Norm(a - b), ws[i * st]);
    }
  }
  NTT(tmp, D, ws, N, !loc, st * 2); // tail recursion
}
 
void NTTMultiply(Int a[], Int b[], Int c[], Int ws[], size_t N) {
  NTTBuildWs(ws, N);
  std::reverse(a + 1, a + N); std::reverse(b + 1, b + N);
  NTT(a, c, ws, N); NTT(b, c, ws, N);
  for (size_t i = 0; i < N; i++) c[i] = Mod(a[i], b[i]);
  NTT(c, b, ws, N);
  Int tN = PowMod(N, P - 2);
  for (size_t i = 0; i < N; i++) c[i] = Mod(c[i], tN);
}
