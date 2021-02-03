/// @tags: luogu; template; hash; string; STL
#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
const int BASE = 67;
inline short shortit(char x) {
    if (islower(x)) return x - 'a' + 1;
    if (isupper(x)) return x - 'A' + 27;
    return x - '0' + 57;
}
ull hashit(const char* c) {
    int l = strlen(c); ull r = 0;
    for (int i=0; i<l; ++i) {
        r *= 67;
        r += shortit(c[i]);
    }
    return r;
}
char buf[1505];

int main() {
    int n; scanf("%d", &n);
    set<ull> S;
    for (int i=1; i<=n; i++) {
        scanf("%s", buf);
        S.insert(hashit(buf));
    }
    printf("%u\n", S.size());
    return 0;
}