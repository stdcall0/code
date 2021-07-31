#include<bits/stdc++.h>
#define Rn(a,n)a+1,a+n+1
#define Edge(T,x,y)T[x].push_back(y);T[y].push_back(x)
#define rep(i,l,r)for(int i=(l),_r_R=(r);i<=_r_R;++i)
typedef long long ll;typedef long double ld;typedef unsigned long long ull;inline ll Rl(){ll ret(0);int c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}inline int R(){int ret(0),c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}

int n;
inline std::string getString() {
  static char buf[105];
  scanf("%s", buf);
  return buf;
}
std::vector<std::string> b;
std::set<std::string> a[26];
const int STA = (1 << 16);
int f[16][STA];

int CNM(int x, int STA) {
  if (f[x][STA]) return f[x][STA];
  int &v = f[x][STA]; v = 0;
  rep(i, 0, n - 1) {
    if (!(STA & (1 << i)) && a[b[x][b[x].size() - 1] - 'A'].count(b[i])) {
      v = std::max(v, CNM(i, STA | (1 << i)));
    }
  }
  return v = v + b[x].size();
}

int main() {
  n = R();
  rep(i, 1, n) {
    static std::string s;
    b.push_back(s = getString());
    a[s[0] - 'A'].insert(s);
  }
  int ans = 0;
  rep(i, 0, n-1) {
    ans = std::max(ans, CNM(i, 1 << i));
  }
  printf("%d\n", ans);
  return 0;
}