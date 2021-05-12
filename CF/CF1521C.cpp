#include<bits/stdc++.h>
#define Rn(a,n)a+1,a+n+1
#define Edge(T,x,y)T[x].push_back(y);T[y].push_back(x)
#define rep(i,l,r)for(int i=(l),_r_R=(r);i<=_r_R;++i)
typedef long long ll;typedef long double ld;typedef unsigned long long ull;inline ll Rl(){ll ret(0);int c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}inline int R(){int ret(0),c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}

const int N = 1e4 + 5;

inline int interact(int t, int i, int j, int x) {
  printf("? %d %d %d %d\n", t, i, j, x);
  fflush(stdout);
  int f = R();
  if (f == -1) std::exit(2);
  return f;
}

std::array<int, N> a;
inline void answer(int n) {
  printf("! ");
  rep(i, 1, n) {
    printf("%d ", a[i]);
  }
  puts("");
  fflush(stdout);
}

int find_last(int n) {
  for (int i = 1; i <= n; i += 2) {
    if (i == n) {
      a[n] = n;
      return n;
    }
    int v = interact(1, i, i + 1, n - 1);
    if (v == n) {
      a[i + 1] = n;
      return i + 1;
    }
    if (v == n - 1) {
      if (interact(1, i + 1, i, n - 1) == n) {
        a[i] = n;
        return i;
      }
    }
  }
  std::exit(1);
}

int main() {
  rep(_Qr, 1, R()) {
    int n = R();
    std::fill(a.begin(), a.end(), 0);
    int m = find_last(n);

    rep(i, 1, n) {
      if (i != m) {
        a[i] = interact(2, i, m, 1);
      }
    }

    answer(n);
  }
  return 0;
}
