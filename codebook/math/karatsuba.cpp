Num mem[MAX_L * 20] , *pmem = mem;

inline void add(Num *a , Num *b , Num *c , int na , int nb) {
    int n = max(na , nb);
    memset(c , 0 , sizeof(Num) * n);
    for(int i = 0; i < na; i++) c[i] = c[i] + a[i];
    for(int i = 0; i < nb; i++) c[i] = c[i] + b[i];
}

void mul(Num *a , Num *b , Num *c , int n) {
    int l = n * 2 - 1;
    memset(c , 0 , sizeof(Num) * l);
    if(n <= 24) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) c[i + j] = c[i + j] + a[i] * b[j];
        }
        return;
    }
    Num *ori_pmem = pmem;
    int sz = n / 2;
    int sz2 = n - sz;
    int nn = max(sz , sz2);
    Num *a1 = a , *a2 = a + sz;
    Num *b1 = b , *b2 = b + sz;
    Num *t1 = pmem;
    pmem += nn;
    Num *t2 = pmem;
    pmem += nn;
    Num *x = pmem;
    pmem += 2 * sz;
    Num *y = pmem;
    pmem += 2 * sz2;
    Num *z = pmem;
    pmem += 2 * nn;
    add(a1 , a2 , t1 , sz , sz2);
    add(b1 , b2 , t2 , sz , sz2);
    mul(a1 , b1 , x , sz);
    mul(a2 , b2 , y , sz2);
    mul(t1 , t2 , z , nn);
    l = 2 * nn - 1;
    int l2 = 2 * sz - 1;
    for(int i = 0; i < l2; i++) {
        c[i] = c[i] + x[i];
        c[i + sz] = c[i + sz] + z[i] - y[i] - x[i];
        c[i + sz + sz] = c[i + sz + sz] + y[i];
    }
    for(int i = l2; i < l; i++) {
        c[i + sz] = c[i + sz] + z[i] - y[i];
        c[i + sz + sz] = c[i + sz + sz] + y[i];
    }
    pmem = ori_pmem;
}
