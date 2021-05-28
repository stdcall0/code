#include<bits/stdc++.h>
#define Rn(a,n)a+1,a+n+1
#define Edge(T,x,y)T[x].push_back(y);T[y].push_back(x)
#define rep(i,l,r)for(int i=(l),_r_R=(r);i<=_r_R;++i)
typedef long long ll;typedef long double ld;typedef unsigned long long ull;inline ll Rl(){ll ret(0);int c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}inline int R(){int ret(0),c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}

int main() {
  int n, a, b;
  n = R(), a = R(), b = R();
  if (a > b) puts("0");
  else if (n == 1) printf("%d\n", a == b);
  else {
    ll mini = 1ll * a * (n - 1) + b;
    ll maxi = 1ll * b * (n - 1) + a;
    printf("%lld\n", maxi - mini + 1);
  }
  return 0;
}
