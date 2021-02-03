#include <bits/stdc++.h>
using namespace std;

namespace Templates {
/*FAST DEFS*/
    #define rep(i, a, b) for(int i(a), i##_END(b); i <= i##_END; i++)
    #define drep(i, a, b) for(int i(a), i##_END(b); i >= i##_END; i--)
    #define forE_(e, y, x, suf) for (int e(hed##suf[x]), y(edges##suf[hed##suf[x]].to); e; e=edges##suf[e].nxt,y=edges##suf[e].to)
    #define forE(e, y, x) for (int e(hed[x]), y(edges[hed[x]].to); e; e=edges[e].nxt,y=edges[e].to)
    #define define(a, b) const int a(b)
    #define define_(typ, a, b) const typ a(b)
    #define mp make_pair
    #define fi first
    #define se second
    #define print_vec(v) for (int i=0; i<v.size(); ++i) printf("%d ", v[i]); puts("")
/*UP&DOWN*/
    template<typename T> inline void down(T&a, const T& b) { a = min(a, b); }
    template<typename T> inline bool down_(T&a, const T& b) { return a > b ? a=b, 1 : 0; }
    template<typename T> inline void up(T&a, const T& b) {a = max(a, b);}
    template<typename T> inline bool up_(T&a, const T& b) { return a < b ? a=b, 1 : 0; }
/*TYPEDEFS*/
    typedef long long ll; typedef long double ld; typedef vector<int> veci; typedef pair<int, int> pii;
/*FASTREADWRITE*/
    struct FastReader { int ch;
        inline int Int() {int nag=0,x=0;while(!isdigit(ch=getchar()))nag=ch=='-';x=ch-'0';while(isdigit(ch=getchar()))x=x*10+ch-'0';return nag?-x:x;}
        inline ll Long() {ll nag=0,x=0;while(!isdigit(ch=getchar()))nag=ch=='-';x=ch-'0';while(isdigit(ch=getchar()))x=x*10+ch-'0';return nag?-x:x;}
        inline ld Double() {ll a=Long(),b=0,c=1;if(ch=='.')while(isdigit(ch=getchar()))b=b*10+ch-'0',c*=10;return a+(ld)1.*b/c;}
        inline char Alpha() {char ch;while(!isalpha(ch=getchar()));return ch;}
        inline char Char() {char ch; while( isspace(ch=getchar()));return ch;}
        inline char Digit() {char ch;while(!isdigit(ch=getchar()));return ch;}
        inline int CStr(char*c) {scanf("%s",c);return strlen(c);}
        inline int Str(string&s,int len=3000) {char buf[len];int l=CStr(buf);s=buf;return l;}
        inline ll operator()() { return Long(); }
        inline int operator()(char*c) { return CStr(c); }
        inline FastReader& operator()(int&a) { return a=Int(),*this; }
        inline FastReader& operator()(ll&a) { return a=Long(),*this; }
        inline int operator()(string&s,int len=3000) { return Str(s,len); }
    } R;
    struct FastWriter {
        inline FastWriter& Int(ll x) {if(x<0){putchar('-');return Int(-x);}if(x/10)Int(x/10);putchar(x%10+'0');return *this;}
        inline FastWriter& Char(char x) {putchar(x);return *this;}
        inline FastWriter& Str(const char*x) {printf("%s",x);return *this;}
        inline FastWriter& StrE(const char*x) {puts(x);return *this;}
        inline FastWriter& Eoln() {putchar('\n');return *this;}
        inline FastWriter& E() {putchar('\n');return *this;}
        inline FastWriter& operator()(int x) { return Int(x); }
        inline FastWriter& operator()(char x) { return Char(x); }
        inline FastWriter& operator()(ll x) { return Int(x); }
        inline FastWriter& operator()(const char*x) { return Str(x); }
    } W;
}; using namespace Templates;

define(N, 80005);
namespace PointMan {
    int pn; struct LL {int x,id; bool operator<(const LL&r) const{return x<r.x;} };
    vector<LL> ps; int poi[N], iop[N];
    inline void init() { }
    inline void addp(int x,int id) { ps.push_back((LL){x,id}); }
    inline void refp() {
        sort(ps.begin(), ps.end()); //pn = unique(ps.begin(), ps.end()) - ps.begin();
        int cc=1; poi[ps[0].id]=1; iop[1]=ps[0].x;
        for (int i=1; i<ps.size(); i++) {
            if (ps[i].x == ps[i-1].x) {
                poi[ps[i].id]=cc;
            } else {
                ++cc; poi[ps[i].id] = cc;
                iop[cc] = ps[i].x;
            }
        }
        pn=cc;
    }
};
namespace SegmentTree {
    #define co int mid = l+r >> 1, pl = p<<1, pr = p<<1|1
    struct TreeNode{
        ll len;    //   该节点上目前激活的线段的长度
        int x, y;  //   该节点左右两端点的 ID
        int val;   //   该节点的目前覆盖 multipler
    } tree[N * 16];
    int m;

    void _build(int p,int l,int r) {
        if (l > r) return;
        tree[p] = (TreeNode) {0, l, r, 0};
        if (l < r) { co; _build(pl, l, mid); _build(pr, mid+1, r); }
    }
    inline void build(int n) { m = n; _build(1, 1, n); }

    inline void _update(int p) {
        int pl = p<<1, pr = p<<1|1; if (tree[p].val) {
            tree[p].len = PointMan::iop[tree[p].y + 1] - PointMan::iop[tree[p].x];
        } else tree[p].len = tree[pl].len + tree[pr].len;
    }
    void _modify(int p,int l, int r, int x, int y, int v) {
        if (r + 1 <= x || y <= l) return;

        if (x <= l && r+1 <= y) {
            tree[p].val += v;
            _update(p);
            return;
        } co;
        _modify(pl, l, mid, x, y, v);
        _modify(pr, mid+1, r, x, y, v);
        _update(p);
    }
    inline void modify(int l, int r, int v) { _modify(1, 1, m, l, r, v); }
    inline ll query() { return tree[1].len; }
    #undef co
};
struct Segment {
    int l, r, v; ll h;
    bool operator < (const Segment& r) const { return h < r.h; }
} seg[N * 2];
int n;
struct ReadTemp { ll a, b, h; } V[N];

int main() {
    PointMan::init();
    R(n); rep(i, 1, n) { R(V[i].a)(V[i].b)(V[i].h);
        PointMan::addp(V[i].a,i*2-1); PointMan::addp(V[i].b,i*2);
    }
    PointMan::refp();
    rep(i, 1, n) {
        seg[i*2-1] = (Segment) {PointMan::poi[i*2-1], PointMan::poi[i*2], -1, V[i].h};
        seg[i*2] = (Segment) {PointMan::poi[i*2-1], PointMan::poi[i*2], 1, 0};
    }
    int m = n*2;
    sort(seg + 1, seg + 1 + m);
    SegmentTree::build(PointMan::pn - 1);

    ll ans = 0;
    rep(i, 1, m-1) {
        SegmentTree::modify(seg[i].l, seg[i].r, seg[i].v);
        ans += SegmentTree::query() * (seg[i+1].h - seg[i].h);
    }
    W(ans).E();
    return 0;
}
