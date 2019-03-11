/**
 * O(n log n log n) suffix array.
 *
 * Use the commented parts for O(n log n) version.
 *
 * Interface:
 * + Let `s` be a null-terminated string of length `n`
 * + After calling `(*this)(s)`...
 * + `sa[0:n]` contains the suffix array
 * + `r[sa[i]] = i` for 0 <= i < n
 * + `h[i] = LCP(s+sa[i], s+sa[i+1])` for 0 <= i < n - 1
 * + `h[n - 1] = 0`
 */
template<int maxn>
struct Suffix_array {
    int sa[maxn], r[maxn], h[maxn], tmp[maxn], cnt[maxn];

    /* void counting_sort(int n) {
        fill_n(cnt, max(n, 256), 0);
        for (int i = 0; i < n; i++)
            cnt[r[i]]++;
        partial_sum(cnt, cnt + max(n, 256), cnt);
        for (int i = n - 1; i >= 0; i--)
            tmp[--cnt[r[sa[i]]]] = sa[i];
        copy_n(tmp, n, sa);
    } */

    void operator () (const char *s) {
        int n = strlen(s);
        if (n == 1) { sa[0] = r[0] = 0; return; }

        copy_n(s, n, r);
        iota(sa, sa + n, 0);
        /* counting_sort(n); */

        for (int g = 1; g < n; g <<= 1) {
            auto cmp = [=](int a, int b) {
                return r[a] != r[b] ? r[a] < r[b] :
                    (a + g >= n || b + g >= n) ? a > b :
                    r[a + g] < r[b + g];
            };

            sort(sa, sa + n, cmp);
            /* for (int i = n - 1, j = n - 1; i >= 0; i--)
                if (sa[i] >= g)
                    sa[j--] = sa[i] - g;
            iota(sa, sa + g, n - g);
            counting_sort(n); */

            tmp[sa[0]] = 0;
            for (int i = 1; i < n; i++)
                tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
            copy_n(tmp, n, r);
        }

        h[n - 1] = 0;
        for (int i = 0; i < n; i++)
            if (r[i] + 1 < n) {
                int x = i ? max(h[r[i - 1]] - 1, 0) : 0;
                while (s[i + x] == s[sa[r[i] + 1] + x])
                    x++;
                h[r[i]] = x;
            }
    }
};