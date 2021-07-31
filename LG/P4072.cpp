#include<bits/stdc++.h>
#define Rn(a,n)a+1,a+n+1
#define Edge(T,x,y)T[x].push_back(y);T[y].push_back(x)
#define rep(i,l,r)for(int i=(l),_r_R=(r);i<=_r_R;++i)
typedef long long ll;typedef long double ld;typedef unsigned long long ull;inline ll Rl(){ll ret(0);int c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}inline int R(){int ret(0),c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}

const int N = 3005;
int s[N], n, m, I;
ll f[N][N];

std::deque<int> Q;
auto sqr = [](auto x) { return x * x; };
inline ll K(int i) { return 2ll * m * s[i]; } 
inline ll Y(int i) { return f[I - 1][i] + 1ll * m * sqr(s[i]) + 2ll * s[n] * s[i]; }
inline ll X(int i) { return s[i]; }
inline ll dX(int i, int j) { return X(j) - X(i); }; inline ll dY(int i, int j) { return Y(j) - Y(i); }
#define head Q[0], Q[1]
#define tail Q[Q.size() - 2], Q[Q.size() - 1]
#define now Q[Q.size() - 1], j

int main() {
  n = R(), m = R();
  assert(n >= m);
  rep(i, 1, n) {
    s[i] = s[i-1] + R();
  }
  rep(j, 1, n) f[0][j] = 1145141919810114514ll;
  rep(i, 1, m) {
    Q.clear(); Q.push_back(0); I = i;
    rep(j, 1, n) {
      while (Q.size() > 1 && K(j) * dX(head) >= dY(head)) Q.pop_front();
      f[i][j] = f[i-1][Q[0]] + 1ll * m * sqr(s[j] - s[Q[0]]) - 2ll * s[n] * (s[j] - s[Q[0]]);
      while (Q.size() > 1 && dY(tail) * dX(now) >= dY(now) * dX(tail)) Q.pop_back();
      Q.push_back(j);
    }
  }
  printf("%lld\n", s[n] * s[n] + f[m][n]);
  return 0;
}
