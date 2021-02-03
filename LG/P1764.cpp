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
#define int long long
define(N, 100005);
struct BIT {
    int tree[N<<2], n;
    BIT(int n_) : n(n_) { memset(tree, 0, sizeof tree); }
    inline int lowbit(int x) { return x & (-x); }
    inline void add(int x, int y) { for (; x <= n; x += lowbit(x)) tree[x] += y; }
    inline int get(int x,int r_=0) { for (; x; x -= lowbit(x)) r_ += tree[x]; return r_; }
};
int a[N], b[N];

signed main() {
    int n; R(n);
    rep(i, 1, n) R(a[i]), b[a[i]] = i;
    BIT bt(n); bt.add(a[n], 1);
    int L = 0;
    drep(i, n-1, 1) {
        L += bt.get(a[i]-1);
        bt.add(a[i], 1);
    }
    int F = L;
    rep(i, 1, n-1) {
        L += n - b[i]*2 + 1; down(F,L);
    }
    W(F).E();
    return 0;
}
