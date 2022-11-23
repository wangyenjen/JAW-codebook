using uint128_t = unsigned __int128;
inline uint64_t Inv(uint64_t b) {
  return ((uint128_t)1 << (64 + 63 - __builtin_clzll(b))) / b;
}
// Calculate a % p
// (x + 62) bits divide by x bits (not power of 2), x <= 62
inline uint64_t Mod(uint128_t a, uint64_t p, uint64_t p_inv) {
  int q = 63 - __builtin_clzll(p);
  uint64_t aa = a >> (q - 1);
  uint64_t res = ((uint128_t)aa * p_inv) >> 65;
  uint128_t r = (uint128_t)(res + 1) * p;
  uint64_t rm = a - r;
  return rm + (p & ((int64_t)rm >> 63));
}
