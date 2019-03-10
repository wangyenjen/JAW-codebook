def solve(n):
    m = 0
    while m < 1 << (n - m):
        m += 1

    # ans1 = 1 + sum(min(1 << i, (1 << (1 << (n - i))) - 1) for i in range(n + 1))
    # ans1 = 1 + sum((1 << i) if i < m else (1 << (1 << (n - i))) - 1 for i in range(n + 1))
    ans1 = (1 << m) + sum((1 << (1 << (n - i))) - 1 for i in range(m, n + 1))

    ans2 = (1 << (1 << (n - m))) * (1 << (n - m)) // 2

    if (1 << (m - 1)) > (1 << (1 << (n - m))) - 1:
        more = (1 << (m - 1)) - ((1 << (1 << (n - m))) - 1)

        p = comb = 1 << (n - m + 1)
        p2 = comb2 = 1 << (n - m)

        for q in range(1, p + 1):
            # print(f'{p} choose {q} is {comb}, {p2} choose {q} is {comb2}')

            match = min(more, comb - comb2)
            ans2 += match * q
            more -= match

            if more == 0:
                break

            comb *= p - q
            comb //= q + 1
            comb2 *= p2 - q
            comb2 //= q + 1

    return ans1, ans2

n = int(open("automaton.in").read())
ans1, ans2 = solve(n)
print(ans1, ans2, file=open("automaton.out", "w"))
