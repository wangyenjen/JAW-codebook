#include <random>
mt19937 rng(880301);
int randint(int lb, int ub)
{ return uniform_int_distribution<int>(lb, ub)(rng); }
