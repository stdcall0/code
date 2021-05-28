#include<bits/stdc++.h>
#define Rn(a,n)a+1,a+n+1
#define Edge(T,x,y)T[x].push_back(y);T[y].push_back(x)
#define rep(i,l,r)for(int i=(l),_r_R=(r);i<=_r_R;++i)
typedef long long ll;typedef long double ld;typedef unsigned long long ull;inline ll Rl(){ll ret(0);int c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}inline int R(){int ret(0),c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}

const int N = 1e6 + 5;
int n, a[N], f[N];
std::deque<int> Q;

int main() {
  n = R();
  rep(i, 1, n) {
    a[i] = R();
  }
  rep(_Qr, 1, R()) {
    int k = R();
    Q.clear();
    Q.push_back(1);
    memset(f, 0, sizeof(f));
    rep(i, 2, n) {
      while (!Q.empty() && Q.front() < i - k) Q.pop_front();
      f[i] = f[Q.front()] + (a[i] >= a[Q.front()]);
      while (!Q.empty()
        && (f[Q.back()] > f[i]
        || (f[Q.back()] == f[i] && a[i] >= a[Q.back()]))) Q.pop_back();
      Q.push_back(i);
    }
    printf("%d\n", f[n]);
  }
  return 0;
}
