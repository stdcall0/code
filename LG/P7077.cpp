#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 5, M = 1e6 + 5, K = N, P = 998244353;
int n, m, q, Q[N], vi[N], eNum, hed[N];
ll muli[N];
struct edge { int to, nxt; } edges[M];
struct FM { // FM
    static int n[4], i1[K], v1[K], v2[K], c3[K]; static vector<int> v3[K];
    inline static int alloc(int typ) { return ++n[typ]; }
};
struct func { int typ, x; } f[N];

inline ll fr() {
    ll ch, neg; while(!isdigit(ch=getchar())) neg = ch == '-'; ll r = ch - '0';
    while(isdigit(ch=getchar())) r = r * 10 + ch - '0'; return neg?-r:r;
}
#define rf(x) (x = fr())

inline void addedge(int x, int y) {
    edges[++eNum] = (edge) {y, hed[x]};
    hed[x] = eNum;
}
void calcMul(int x) {
    if (muli[x]) return;
    muli[x] = muli[x] = f[x].typ == 2 ? FM::v2[f[x].x] : 1;
    for (int e = hed[x]; e; e=edges[e].nxt) {
        int y = edges[e].to; calcMul(y);
        (muli[x] *= muli[y]) %= P;
    }
}

int main() {
    n = fr(); for (int i=1; i<=n; i++) vi[i] = fr();
    m = fr(); for (int i=1; i<=m; i++) {
        int T = fr(); f[i] = (func){T, FM::alloc(T)};
        switch(T) {
                   case 1: FM::i1[f[i].x] = fr(), FM::v1[f[i].x] = fr() % P;
            break; case 2: FM::v2[f[i].x] = fr() % P;
            break; case 3: FM::c3[f[i].x] = fr(); for (int j=0; j<FM::c3[f[i].x]; ++j) {
                FM::v3[f[i].x].push_back(fr());
                addedge(i, *--FM::v3[f[i].x].end());
            }
        }
    }
    q = fr(); for (int i=q; i>=1; i--) vi[i] = fr();
    for (int i=1; i<=n; ++i) if (!muli[i]) calcMul(i);
    
    return 0;
}
