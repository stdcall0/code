#include<bits/stdc++.h>
#define Rn(a,n)a+1,a+n+1
#define Edge(T,x,y)T[x].push_back(y);T[y].push_back(x)
#define rep(i,l,r)for(int i=(l),_r_R=(r);i<=_r_R;++i)
typedef long long ll;typedef long double ld;typedef unsigned long long ull;inline ll Rl(){ll ret(0);int c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}inline int R(){int ret(0),c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}

int x[10005];
int a[16005], b[16005], c[16005];
inline int sig(int x) { return x > 0 ? 1 : -1; }
#define fi(y) x[abs(y)] = sig(y)
#define ch(y) (x[abs(y)] == sig(y))

int main() {
  int n, m;
  n = R(), m = R();
  rep(i, 1, m) {
    a[i] = R(), b[i] = R(), c[i] = R();
    if (!x[abs(a[i])]) fi(a[i]);
    else if (!x[abs(b[i])]) fi(b[i]);
    else fi(c[i]);
  }
  srand(time(0));
  while (1) {
    bool t = 0;
    rep(i, 1, m) {
      if (ch(a[i]) || ch(b[i]) || ch(c[i])) {
        continue;
      }
      t = 1;
      int he = rand() % 3;
      if (he == 0) fi(a[i]);
      else if (he == 1) fi(b[i]);
      else fi(c[i]);
    }
    if (t == 0) {
      rep(i, 1, n) printf("%d ", std::max(0, x[i]));
      return 0;
    }
  }
  return 0;
}
