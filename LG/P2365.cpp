#include<bits/stdc++.h>
#define Rn(a,n)a+1,a+n+1
#define Edge(T,x,y)T[x].push_back(y);T[y].push_back(x)
#define rep(i,l,r)for(int i=(l),_r_R=(r);i<=_r_R;++i)
typedef long long ll;typedef long double ld;typedef unsigned long long ull;inline ll Rl(){ll ret(0);int c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}inline int R(){int ret(0),c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}

const int N = 3e5 + 5;
int n;
ll s, t[N], c[N], f[N];

std::deque<int> Q;
inline ll dX(int i, int j) { return c[j] - c[i]; }
inline ll dY(int i, int j) { return f[j] - f[i] - c[j] * s + c[i] * s; }
#define head Q[0], Q[1]
#define tail Q[Q.size() - 2], Q[Q.size() - 1]

inline int find(int i) {
  int l = 0, r = Q.size() - 1, ret = Q.size() - 1;
  while (l <= r) {
    static int mid;
    mid = l + r >> 1;
    if (dY(Q[mid], Q[mid+1]) > t[i] * dX(Q[mid], Q[mid+1])) {
      ret = mid; r = mid - 1;
    } else l = mid + 1;
  }
  return ret;
}

int main() {
  n = R(), s = Rl();
  rep(i, 1, n) {
    t[i] = t[i - 1] + Rl();
    c[i] = c[i - 1] + Rl();
  }
  Q.push_back(0);
  rep(i, 1, n) {
    int p = Q[find(i)];
    f[i] = f[p] + t[i] * (c[i] - c[p]) + s * (c[n] - c[p]);
    while (Q.size() > 1 && dY(tail) * dX(Q[Q.size() - 1], i) >= dY(Q[Q.size() - 1], i) * dX(tail)) Q.pop_back();
    Q.push_back(i);
  }
  printf("%lld\n", f[n]);
  return 0;
}