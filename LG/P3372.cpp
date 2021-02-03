// * Template: Segment Tree
// * Op: [L,R]+,Q
#include <bits/stdc++.h>
using namespace std;

auto fast_io = [](){ cin.tie(0); ios::sync_with_stdio(0); };
const int N = 100005; typedef long long ll;
int n, m;
ll a[N * 16], tag[N * 16];

inline void down(int p, int l, int r) {
    if (tag[p]) { int mid = l + r >> 1;
        a[p << 1] += tag[p] * (mid - l + 1);
        a[p << 1 | 1] += tag[p] * (r - mid);
        tag[p << 1] += tag[p]; tag[p << 1 | 1] += tag[p]; tag[p] = 0;
    }
}
inline void up(int p, int l, int r) {
    if (l >= r) return;
    a[p] = a[p << 1] + a[p << 1 | 1];
}
void Add(int L, int R, ll x, int p=1, int l=1, int r=n) {
    if (L > R) return;
    if (L == l && R == r) {
        tag[p] += x; a[p] += 1ll * (r-l+1) * x; return;
    }
    down(p, l, r); int mid = l+r>>1;
    Add(L,min(mid, R),x,p<<1,l,mid);
    Add(max(mid+1, L),R,x,p<<1|1,mid+1,r);
    up(p, l, r);
}
ll Sum(int L, int R, int p=1, int l=1, int r=n) {
    if (L > R) return 0; down(p, l, r);
    if (L == l && R == r) return a[p];
    int mid = l+r>>1; ll re = 0;
    re += Sum(L,min(mid, R),p<<1,l,mid);
    re += Sum(max(mid+1, L),R,p<<1|1,mid+1,r);
    return re;
}

int main() {
    fast_io(); cin >> n >> m;
    int opt, x, y; ll k; for (int i=1; i<=n; i++) {
        cin >> k; Add(i, i, k);
    }
    while (m--) {
        cin >> opt >> x >> y;
        switch(opt) {
            case 1: cin >> k; Add(x,y,k); break;
            case 2: cout << Sum(x,y) << endl;
        }
    }
    return 0;
}
