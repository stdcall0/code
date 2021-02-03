// * Template: Minimal Generation Tree
#include <bits/stdc++.h>
using namespace std;

const int N = 5005, M = 200005;
int n, m;
struct uset {
    int fa[N], n;
    inline void setN(int pN) { n = pN; for (int i=1; i<=n; i++) fa[i] = i; }
    int findset(int x) { return x == fa[x] ? x : fa[x] = findset(fa[x]); }
    bool merge(int x, int y) {
        x = findset(x), y = findset(y);
        if (x == y) return 0;
        return fa[x] = y;
    }
} U;
struct edge {
    int x, y, z;
    bool operator< (const edge& r) const { return z < r.z; }
}; vector<edge> v;

int main() {
    cin.tie(nullptr); ios::sync_with_stdio(0);
    cin >> n >> m;
    for (int i=1; i<=m; i++) {
        int x,y,z; cin >> x >> y >> z;
        v.push_back({x,y,z});
    }
    sort(v.begin(), v.end());
    U.setN(n); int sel = 0, sle = 0;
    for (int i=0; i<m; i++) {
        if (U.merge(v[i].x, v[i].y)) {
            ++sel, sle += v[i].z;
        }
    }
    sel == n-1 ? printf("%d\n", sle) : printf("orz\n");
    return 0;
}
