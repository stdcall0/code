#include<bits/stdc++.h>
#define Rn(a,n)a+1,a+n+1
#define Edge(T,x,y)T[x].push_back(y);T[y].push_back(x)
#define rep(i,l,r)for(int i=(l),_r_R=(r);i<=_r_R;++i)
typedef long long ll;typedef long double ld;typedef unsigned long long ull;inline ll Rl(){ll ret(0);int c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}inline int R(){int ret(0),c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}

int dep;
std::set<ll> es;
ll now[114514], ans[114514];
bool once = false;

inline bool better() {
  for (int i = dep; i >= 1; --i) {
    if (now[i] < ans[i]) return true;
    if (now[i] > ans[i]) return false;
  }
  return false;
}

void dfs(ll a, ll b, int cnt, ll lst = 0) {
  if (cnt == dep) {
    if (b % a || es.count(b / a)) return;
    now[dep] = b / a;
    if (once || better()) once = 0, memcpy(ans, now, sizeof(ans));
    return;
  }
  for (ll i = std::max(b / a + 1, lst); a * i < b * (dep - cnt + 1); ++i) {
    if (es.count(i)) continue;
    now[cnt] = i;
    static ll x, y, z;
    x = a * i - b; y = i * b; z = std::__gcd(x, y);
    dfs(x / z, y / z, cnt + 1, i + 1);
  }
}

int main() {
  int a, b;
  rep(_Qr, 1, R()) {
    a = R(), b = R();
    es.clear(); rep(j, 1, R()) es.insert(Rl());
    if (a == 1) {
      printf("Case %d: 1/%d=1/%d\n", _Qr, b, b);
      continue;
    }
    dep = 1; once = 1; do ++dep, dfs(a, b, 1); while (once);
    printf("Case %d: %d/%d=", _Qr, a, b);
    rep(i, 1, dep) {
      printf(dep == i ? "1/%d" : "1/%d+", ans[i]);
    }
    puts("");
  }

  return 0;
}