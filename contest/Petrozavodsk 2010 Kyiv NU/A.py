from math import gcd

fact = [1]
for i in range(1, 10000):
    fact.append(fact[-1] * i)

def solve(n):
    s = 0
    for i in range(2, n):
        s += fact[n - 1] ** 2 // (fact[n - i - 1] * fact[i] * i)

    p = fact[n - 1]

    return s % p / p

def solve2(n):
    ans = 0
    for i in range(1, n):
        ans = (ans + (2 ** i - 1) % i / i) % 1
    return ans

for n in range(2, 41):
    print(n, solve(n), solve2(n))
