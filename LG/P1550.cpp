#include <bits/stdc++.h>
using namespace std;

int r() { static int r; scanf("%d", &r); return r; }
int n;
struct edge { int frm, to, val; bool operator< (const edge&r) const \
    { return val < r.val; }}; vector<edge> E;
template<int MAX_SIZE>
struct UnionSet {
    int fa[MAX_SIZE + 5];
    inline void makeset(int siz) { for (int i=1; i<=siz; ++i) fa[i] = i; }
    inline int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
    inline bool same(int x, int y) { return find(x) == find(y); }
    inline bool merge(int x, int y) { return (x = find(x)) == (y = find(y)) ? 0 : fa[x]=y; }
}; UnionSet<300> U;
static int f = ([]() { n = r();
    for (int i=0; i<=n; i++) for (int j=1; j<=n; j++) E.push_back((edge){i?i:n+1, j, r()});
    sort(E.begin(), E.end()); U.makeset(n+1);
    int A=0;for (auto& e:E) if (U.merge(e.frm, e.to)) A+=e.val;
    return printf("%d\n", A), exit(0), 0;
})();


int main() {

    cout << "Farmer John! NMSL! haha!\n";

    return 0;
}