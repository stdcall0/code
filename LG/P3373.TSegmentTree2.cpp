#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
inline int rd() {
    int r; scanf("%d", &r); return r;
}

const int N = 8e5 + 5;
int n, m, P, a[N];
struct SegmentTree {
    struct TrNode { int L,R, l,r; ll v, add, mul; } a[N]; int c=1;
#define ex(x) (x > 0 && x <= c)
#define exv(x) (x.L != -1)
#define len(x) (x.R - x.L + 1)
#define ga TrNode& x = a[xi]; int mid = x.L + x.R >> 1
// #define xa TrNode& x = a[xi], l = a[a[xi].l], r = a[a[xi].r]; int mid = x.L + x.R >> 1
#define nm TrNode& l = a[x.l], &r = a[x.r]
    void Build(int xi = 1) {
        ga; if (x.L == x.R) return (void)(x.v = ::a[x.L], x.add = 0, x.mul = 1);
        Build((a[++c].L = x.L, a[c].R = mid, x.l=c));
        Build((a[++c].L = mid + 1, a[c].R = x.R, x.r=c));
        x.add = 0, x.mul = 1, x.v = (a[x.l].v + a[x.r].v) % P;
        // printf("Node %d, L %d R %d with val %lld range [%d,%d]\n", xi, x.l,x.r,x.v,x.L,x.R);
    }
    inline void Init() { a[0].L = -1, c = 1, a[1].L = 1, a[1].R = n; Build(); }
    inline void Down(TrNode& x) {
        nm; if (x.add || x.mul != 1) {
            // printf("Pushing Down in Node [%d,%d], FLG %lld %lld - l %d, r %d\n", x.L,x.R,x.add, x.mul, x.l,x.r);
            // x.v = ((x.v * x.mul) + x.add * len(x)) % P;
            if exv(l)
                l.v = ((l.v * x.mul) + x.add * len(l)) % P,
                r.v = ((r.v * x.mul) + x.add * len(r)) % P,
                l.mul *= x.mul, r.mul *= x.mul,
                l.add = l.add * x.mul + x.add,
                r.add = r.add * x.mul + x.add,
                l.mul %= P, r.mul %= P,
                l.add %= P, r.add %= P;
            // printf("Pushing down After: [%d,%d].v %lld [%d,%d].v %lld\n", l.L,l.R,l.v, r.L,r.R,r.v);
            x.add = 0, x.mul = 1;
        }
    }
    inline void Up(TrNode& x) {
        nm; x.v = (l.v + r.v) % P;
        // printf("Up: Node[%d,%d] now has val %lld\n", x.L,x.R,x.v);
    }
    inline void Mul(int L, int R, int k, int xi = 1) {
        ga; if (L <= x.L && x.R <= R) return (void)((x.add*=k) %= P, (x.mul*=k) %= P, (x.v *= k) %= P);
        Down(x); if (L <= mid) Mul(L, R, k, x.l); if (mid < R) Mul(L, R, k, x.r); Up(x);
    }
    inline void Add(int L, int R, int k, int xi = 1) {
        ga; if (L <= x.L && x.R <= R) return (void)((x.add+=k) %= P, (x.v += 1ll*k*len(x)%P)%=P);
        Down(x); if (L <= mid) Add(L, R, k, x.l); if (mid < R) Add(L, R, k, x.r); Up(x);
    }
    inline ll Qry(int L, int R, int xi = 1) {
        ga; //printf("Qrying [%d, %d] in [%d, %d] - v%lld Fl %lld,%lld\n", x.L, x.R, L, R, x.v, x.add, x.mul);
        if (L <= x.L && x.R <= R) return x.v; Down(x); 
        ll re=0; if (L <= mid) re+=Qry(L, R, x.l); if (mid < R) re+=Qry(L, R, x.r);
        Up(x); return re % P;
    }
} T;

int main() {
    n = rd(), m = rd(), P = rd();
    for (int i=1; i<=n; i++) a[i] = rd() % P;
    T.Init(); int ty, x,y,k;
    for (int i=1; i<=m; i++) {
        ty = rd(), x = rd(), y = rd();
        if (ty == 3) printf("%lld\n", T.Qry(x, y) % P);
        else {
            k = rd();
            ty == 1 ? T.Mul(x, y, k) : T.Add(x, y, k);
        }
    }
    return 0;
}
