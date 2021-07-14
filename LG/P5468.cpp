#include<bits/stdc++.h>
#define Rn(a,n)a+1,a+n+1
#define Edge(T,x,y)T[x].push_back(y);T[y].push_back(x)
#define rep(i,l,r)for(int i=(l),_r_R=(r);i<=_r_R;++i)
typedef long long ll;typedef long double ld;typedef unsigned long long ull;inline ll Rl(){ll ret(0);int c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}inline int R(){int ret(0),c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}
struct edge { int to, L, R; inline bool operator<(const edge& res) const { return L > res.L;  } };

const int N = 1e5 + 5, TI = 1e3 + 5;
int n, m, A, B, C;
std::vector<edge> g[N];
auto YCZ = [](int t) { return A * t * t + B * t + C; };
int f[N][TI], ans = 0x3f3f3f3f;
void ycz(int x, int tim, int ang) {
  if (ang > f[x][tim]) return;
  f[x][tim] = ang;
  if (x == n) {
    ans = std::min(ans, ang + tim);
    return;
  }
  for (auto& _ : g[x]) {
    if (_.L < tim) break;
    ycz(_.to, _.R, YCZ(_.L - tim) + ang);
  }
}

int main() {
  n = R(), m = R(), A = R(), B = R(), C = R();
  rep(i, 1, m) {
    static int x, y, p, q; x = R(), y = R(), p = R(), q = R();
    g[x].push_back((edge){y, p, q});
  }
  rep(i, 1, n) sort(g[i].begin(), g[i].end()), std::fill(f[i], f[i] + (TI - 1), 0x3f3f3f3f);
  ycz(1, 0, 0); printf("%d\n", ans);
  return 0;
}
