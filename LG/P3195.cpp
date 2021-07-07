#include<bits/stdc++.h>
#define Rn(a,n)a+1,a+n+1
#define Edge(T,x,y)T[x].push_back(y);T[y].push_back(x)
#define rep(i,l,r)for(int i=(l),_r_R=(r);i<=_r_R;++i)
typedef long long ll;typedef long double ld;typedef unsigned long long ull;inline ll Rl(){ll ret(0);int c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}inline int R(){int ret(0),c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}

const int N = 5e4 + 5;
int n, L;
ll c[N], f[N];

std::deque<int> Q;
auto sqr = [](auto x) { return x * x; };
inline ll X(int i) { return c[i]; } 
inline ll Y(int i) { return f[i] + sqr(c[i]); }
inline ll K(int i) { return (c[i] - L) << 1ll; }
inline ll B(int i) { return f[i] - sqr(c[i] - L); }

inline ll dX(int i, int j) { return X(j) - X(i); }; inline ll dY(int i, int j) { return Y(j) - Y(i); }
#define head Q[0], Q[1]
#define tail Q[Q.size() - 2], Q[Q.size() - 1]
#define now Q[Q.size() - 1], i

int main() {
  n = R(), L = R() + 1;
  rep(i, 1, n) {
    c[i] = c[i - 1] + R();
  }
  rep(i, 1, n) c[i] = c[i] + i;
  f[0] = 0; Q.push_back(0);
  rep(i, 1, n) {
    while (Q.size() > 1 && K(i) * dX(head) >= dY(head)) Q.pop_front();
    f[i] = f[Q[0]] + sqr(c[i] - c[Q[0]] - L);
    while (Q.size() > 1 && dY(tail) * dX(now) >= dY(now) * dX(tail)) Q.pop_back();
    Q.push_back(i);
  }
  printf("%lld\n", f[n]);
  return 0;
}
