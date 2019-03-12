/**
 * s[i - z[i] + 1 : i + z[i]] is palindrome.
 */
void manacher(char *s, int *z, int n) {
    z[0] = 1;
    for (int i = 1, l = 0, r = 1; i < n; i++) {
        int x = i < r ? min(r - i, z[2 * l - i]) : 1;
        while (i - x >= 0 && i + x < n && s[i - x] == s[i + x])
            x++;
        z[i] = x;
        if (i + x > r)
            l = i, r = i + x;
    }
}
char s[3001], s2[6002];
int z[6001];
int main() {
    scanf("%3000s", s);
    int n = strlen(s);
    for (int i = 0; i < n; i++)
        s2[2 * i] = '.', s2[2 * i + 1] = s[i];
    s2[2 * n] = '.';
    int m = 2 * n + 1;
    s2[m] = '\n';
    manacher(s2, z, m);
    int maxi = *max_element(z, z + m);
    int cnt = count(z, z + m, maxi);
    printf("%d %d\n", maxi - 1, cnt);
}
