#include<bits/stdc++.h>
#define Rn(a,n)a+1,a+n+1
#define Edge(T,x,y)T[x].push_back(y);T[y].push_back(x)
#define rep(i,l,r)for(int i=(l),_r_R=(r);i<=_r_R;++i)
typedef long long ll;typedef long double ld;typedef unsigned long long ull;inline ll Rl(){ll ret(0);int c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}inline int R(){int ret(0),c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}

const int N = 2e6 + 5;
int a[N], d, n;
ll s[N], p;
std::deque<int> Q;
inline ll fx(int x) { return s[x] - s[x - d]; }

int main() {
  n = R(); p = Rl(); d = R();
  rep(i, 1, n) {
    a[i] = R();
    s[i] = s[i - 1] + a[i];
  }

  Q.push_back(d);
  int ans = d;
  int L = 1;

  rep(i, d + 1, n) {
    while (Q.size() && fx(i) > fx(Q.back())) Q.pop_back();
    Q.push_back(i);
    while (Q.size() && s[i] - s[L-1] - fx(Q.front()) > p) {
      ++L;
      while (Q.size() && Q.front() - d < L - 1) Q.pop_front();
    }
    ans = std::max(ans, i - L + 1);
  }

  printf("%d\n", ans);
  return 0;
}
