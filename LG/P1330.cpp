#include <bits/stdc++.h>
using namespace std;
#define USE_OPTIMIZE

namespace Templates {
/*OPTIMIZATIONS*/
#ifdef USE_OPTIMIZE
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#endif
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

define(N, 10005); define(M, 200005);
int n, m, hed[N], tot, vis[N], col[N];
struct edge { int to, nxt; } edges[M];

inline void addedge(int x, int y) {
    edges[++tot] = (edge) {y, hed[x]};
    hed[x] = tot;
}
inline int dfs(int x, int nd, int fil) {
    vis[x] = fil; col[x] = nd; int ret = 0;
    forE(e, y, x) {
        if (vis[y] != fil) {
            ret += dfs(y, 3-nd, fil);
        } else if (col[y] == nd) return 2e9;
    }
    return ret + (nd == 1);
}
int main() {
    int x,y; R(n)(m);
    rep(i, 1, m) {
        R(x)(y); addedge(x,y); addedge(y,x);
    }
    int minV = 0; bool ok = 1;
    rep(i, 1, n) {
        if (!vis[i]) {
            int l = dfs(i, 1, 1),
                r = dfs(i, 2, 2);
            if (l >= 2e9 && r >= 2e9) ok = 0;
            //printf("WDNMD%d %d\n", l,r);
            minV += min(l, r);
        }
    }
    !ok ? W("Impossible") : W(minV); W.E(); return 0;
}
