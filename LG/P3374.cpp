// * Template: BIT
// * [X]+ [L,R]Q
#include <bits/stdc++.h>
using namespace std;

const int N = 500005;

struct BIT {
    int tree[N * 8], n;
    BIT() { memset(tree, 0, sizeof(tree)); }
    inline void setN(int pN) { n = pN; }
    inline int lowbit(int x) { return x & (-x); }
    inline int sum(int r) { int _=0; for (; r; r -= lowbit(r)) _ += tree[r]; return _; }
    inline int range(int l, int r) { return sum(r) - sum(l-1); }
    inline void add(int r, int y) { for (; r <= n; r += lowbit(r)) tree[r] += y; }
} b;

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int _, n, m, opt,x,y; cin >> n >> m; b.setN(n);
    for (int i=1; i <= n; i++) {
        cin >> _;  b.add(i, _);
    }
    while (m--) {
        cin >> opt >> x >> y;
        switch(opt) {
            case 1: b.add(x,y); break;
            case 2: cout << b.range(x,y) << endl;
        }
    }
    return 0;
}
