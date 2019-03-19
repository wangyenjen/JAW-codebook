#include <cstdio>
#include <vector>
#include <variant>
#include <cctype>
using namespace std;

constexpr long long maxnum = 1'000'000'000'000;

struct Long {
    long long num; // or maxnum + 1
    
    Long(): num() {}
    Long(long long n): num(min(maxnum + 1, n)) {}
    explicit operator long long () const { return num; }

    Long &operator += (Long r);
};

Long operator + (Long l, Long r) {
    return l.num + r.num;
}
Long operator * (Long l, Long r) {
    return (r.num && l.num > maxnum / r.num) ? maxnum + 1 : l.num * r.num;
}
Long &Long::operator += (Long r) {
    return *this = *this + r;
}

struct Elem;

struct Prog {
    vector<Elem> v;
    Long cnt[26], cnt2[26];
    Prog(): v(), cnt(), cnt2() {}
    Prog(vector<Elem> &&vv): v(move(vv)), cnt(), cnt2() {}
    void operator () ();
    void operator () (int limit);
};

struct Elem {
    variant<char, pair<int, Prog>> v;
    Long cnt[26], cnt2[26];
    Elem(char c): v(c), cnt(), cnt2() {}
    Elem(pair<int, Prog> &&p): v(move(p)), cnt(), cnt2() {}
    void operator () ();
    void operator () (int limit);
};

void Prog::operator () () {
    for (Elem &e : v) {
        e();
        for (int i = 0; i < 26; i++)
            cnt[i] += e.cnt[i];
    }
}
void Elem::operator () () {
    if (v.index() == 0) {
        cnt[get<0>(v) - 'a'] += 1;
    } else {
        auto &p = get<1>(v);
        p.second();
        for (int i = 0; i < 26; i++)
            cnt[i] += p.first * p.second.cnt[i];
    }
}
void Prog::operator () (int limita) {
    for (Elem &e : v) {
        if (limita == 0)
            break;

        if (limita > e.cnt[0].num) {
            limita -= e.cnt[0].num;
            for (int i = 0; i < 26; i++)
                cnt2[i] += e.cnt[i];
        } else {
            e(limita);
            for (int i = 0; i < 26; i++)
                cnt2[i] += e.cnt2[i];
            break;
        }
    }
}
void Elem::operator () (int limita) {
    if (limita == 0)
        return;
    if (v.index() == 0) {
        cnt2[get<0>(v) - 'a'] += 1;
    } else {
        auto &p = get<1>(v);

        long long ra = p.second.cnt[0].num;
        int fullrep = ra ? min((long long) p.first, (limita - 1) / ra) : p.first;

        for (int i = 0; i < 26; i++)
            cnt2[i] += fullrep * p.second.cnt[i];
        limita -= fullrep * ra;

        if (fullrep < p.first) {
            p.second(limita);
            for (int i = 0; i < 26; i++)
                cnt2[i] += p.second.cnt2[i];
        }
    }
}

Prog read_prog();

Elem read_elem() {
    if (char c = getchar(); isalpha(c))
        return c;
    else
        ungetc(c, stdin);

    int x;
    scanf("%d", &x);
    getchar(); // (
    Prog p = read_prog();
    getchar(); // )

    return make_pair(x, move(p));
}

Prog read_prog() {
    Prog p;

    char c;
    while (isalnum(c = getchar())) {
        ungetc(c, stdin);
        p.v.push_back(read_elem());
    }
    ungetc(c, stdin);

    return move(p);
}

int main() {
    freopen("az.in", "r", stdin);
    // freopen("az.out", "w", stdout);

    Prog p = read_prog();
    p();

    int k;
    scanf("%d", &k);
    p(k);

    for (int i = 0; i < 26; i++)
        if (p.cnt2[i].num)
            printf("%c %lld\n", 'a' + i, p.cnt2[i].num > maxnum ? -1 : p.cnt2[i].num);
}
