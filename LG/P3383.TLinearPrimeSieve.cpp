// Template: 线性筛素数
#include <bits/stdc++.h>
// #pragma GCC optimize("Ofast","-funroll-loops","-fdelete-null-pointer-checks")
#pragma GCC target("ssse3","sse3","sse2","sse","avx2","avx")
using namespace std;
int n, q; bool b[100000010];
int primes[6000010], cnt = 0;

void doSieve() {
    memset(b, 0, sizeof(b));
    for (int i=2; i<=n; ++i) {
        if (!b[i]) primes[++cnt] = i;
        for (int j=1; j<=cnt; j++) {
            int p = primes[j];
            if (i * p > n) break;
            b[i * p] = 1;
            if (i % p); else break;
        }
    }
}

int main() {
    scanf("%d%d", &n,&q);
    doSieve();
    while (q--) {
        int k; scanf("%d", &k);
        printf("%d\n", primes[k]);
    }
    return 0;
}
