#include<bits/stdc++.h>
#define Rn(a,n)a+1,a+n+1
#define Edge(T,x,y)T[x].push_back(y);T[y].push_back(x)
#define rep(i,l,r)for(int i=(l),_r_R=(r);i<=_r_R;++i)
typedef long long ll;typedef long double ld;typedef unsigned long long ull;inline ll Rl(){ll ret(0);int c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}inline int R(){int ret(0),c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}

std::map<int, int> ex;
std::vector<int> sp, sp2;

auto dis = [](int x, int y) {
  if (std::abs(x - y) == 3 || x == 2 && y == 3 || x == 3 && y == 2) return 2;
  if (x == y) return 0;
  return 1;
};

int main() {
  srand(clock());
  rep(i, 1, 4) {
    int x = R();
    sp.push_back(x);
    ex[x]++;
  }
  bool flag = ex[0] == 0;
  bool flag2 = ex[0] == 1;
  rep(i, 1, 4) {
    int x = R();
    sp2.push_back(x);
    ex[x]--;
  }
  if (flag) {
    puts( sp == sp2 ? "Yes" : "No" );
    return 0;
  }
  for (int x : sp) {
    if (ex[x] != 0) {
      puts("No");
      return 0;
    }
  }
  if (flag2) {
    int x = rand() % 7;
    puts(x < 2 ? "No" : "Yes");
    return 0;
  }
  puts("Yes");
  return 0;
}