#include<bits/stdc++.h>
#define Rn(a,n)a+1,a+n+1
#define Edge(T,x,y)T[x].push_back(y);T[y].push_back(x)
#define rep(i,l,r)for(int i=(l),_r_R=(r);i<=_r_R;++i)
typedef long long ll;typedef long double ld;typedef unsigned long long ull;inline ll Rl(){ll ret(0);int c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}inline int R(){int ret(0),c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}

int a[100005];
ll f[100005][2], s[100005];
std::deque<int> Q;

inline ll fx(int x) { return f[x][0] - s[x]; }

int main() {
  int n, k;
  n = R(), k = R();
  rep(i, 1, n) {
    a[i] = R();
    s[i] = s[i - 1] + a[i];
  }

  f[1][1] = a[1];
  Q.push_back(0);

  rep(i, 1, n) {
    f[i][0] = std::max(f[i-1][0], f[i-1][1]);

    while (Q.size() && Q.front() < i - k) Q.pop_front();
    f[i][1] = fx(Q.front()) + s[i];
    while (Q.size() && fx(Q.back()) <= fx(i)) Q.pop_back();
    Q.push_back(i);
  }

  printf("%lld\n", std::max(f[n][0], f[n][1]));
  return 0;
}
