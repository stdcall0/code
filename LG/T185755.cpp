#include<bits/stdc++.h>
#define Rn(a,n)a+1,a+n+1
#define Edge(T,x,y)T[x].push_back(y);T[y].push_back(x)
#define rep(i,l,r)for(int i=(l),_r_R=(r);i<=_r_R;++i)
typedef long long ll;typedef long double ld;typedef unsigned long long ull;inline ll Rl(){ll ret(0);int c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}inline int R(){int ret(0),c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}

int a[805], n, c[805][11];
std::multiset<short> b[805], S;

  auto q = [](int l, int r){
    int k = std::log2(r - l + 1);
    return std::min(c[l][k], c[r-(1<<k)+1][k]);
  };

bool chk() {
  rep(i, 1, n) c[i][0] = a[i];
  for(int j=1;(1<<j)<=n;j++)for(int i=1;i+(1<<j)-1<=n;i++)c[i][j] = std::min(c[i][j-1], c[i+(1<<j-1)][j-1]);

  rep(L, 2, n - 1) {
    S.clear();
    rep(i, 1, n - L + 1) {
      short v = q(i, i + L - 1);
      if (b[L].count(v) == 0) return false;      
      S.insert(v);
    }
    if (S != b[L]) return false;
  }
  return true;
}

int main() {
  srand(clock());
  n = R();
  rep(i, 1, n) a[i] = R();
  for (int i = n - 1; i >= 1; i--) {
    rep(j, 1, i) b[n-i+1].insert(R());
  }
  std::sort(a + 1, a + 1 + n);
  if (chk()) {
    rep(i, 1, n) {
      printf("%d ", a[i]);
    }
    return 0;
  }
  while (1) {
    std::random_shuffle(a + 1, a + 1 + n);

    if (chk()) {
      rep(i, 1, n) {
        printf("%d ", a[i]);
      }
      return 0;
    }
  }
  return 0;
}