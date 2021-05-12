#include<bits/stdc++.h>
#define Rn(a,n)a+1,a+n+1
#define Edge(T,x,y)T[x].push_back(y);T[y].push_back(x)
#define rep(i,l,r)for(int i=(l),_r_R=(r);i<=_r_R;++i)
typedef long long ll;typedef long double ld;typedef unsigned long long ull;inline ll Rl(){ll ret(0);int c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}inline int R(){int ret(0),c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}

const int N = 1e5 + 5;
int n, a[N];

typedef std::array<int, 4> Opt;
std::vector<Opt> opt;
inline void make_opt(int i, int j, int x, int y) {
  opt.push_back({i, j, x, y});
}

int main() {
  rep(_Qr, 1, R()) {
    n = R();
    rep(i, 1, n) {
      a[i] = R();
    }
    int mi = std::distance(a, std::min_element(Rn(a, n)));
    opt.clear();
    if (mi != 1) make_opt(1, mi, a[mi], a[1]), std::swap(a[1], a[mi]);
    rep(i, 2, n) {
      if (a[i] != a[1] + i - 1) {
        make_opt(1, i, a[1], a[1] + i - 1);
      }
    }
    printf("%d\n", opt.size());
    for (auto &o : opt) {
      printf("%d %d %d %d\n", o[0], o[1], o[2], o[3]);
    }
  }
  return 0;
}
