/// @tags: luogu; template; unionset
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
template<typename T>
void R(T& r) {
    char c; bool neg; r = 0;
    while (!isdigit(c = getchar())) neg = c == '-';
    r = c - '0'; while (isdigit(c = getchar())) r *= 10, r += c - '0';
    if (neg) r = -r;
}
ll R() { ll r; return R(r), r; }

int n,m;
template<int MAX_SIZE>
struct UnionSet {
    int fa[MAX_SIZE + 5];
    inline void makeset(int siz) { for (int i=1; i<=siz; ++i) fa[i] = i; }
    inline int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
    inline bool same(int x, int y) { return find(x) == find(y); }
    inline bool merge(int x, int y) { return (x = find(x)) == (y = find(y)) ? 0 : fa[x]=y; }
}; UnionSet<(int)1e4> U;

int main() {
    R(n), R(m); U.makeset(n);
    for (int i=1; i<=m; i++) {
        int T,x,y; R(T),R(x),R(y);
        if (T == 1) U.merge(x, y);
        else puts(U.same(x, y) ? "Y" : "N");
    }
    return 0;
}
