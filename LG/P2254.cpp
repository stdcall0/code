#include<bits/stdc++.h>
#define Rn(a,n)a+1,a+n+1
#define Edge(T,x,y)T[x].push_back(y);T[y].push_back(x)
#define rep(i,l,r)for(int i=(l),_r_R=(r);i<=_r_R;++i)
typedef long long ll;typedef long double ld;typedef unsigned long long ull;inline ll Rl(){ll ret(0);int c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}inline int R(){int ret(0),c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}

const int N = 205;
int n, m, K;
bool S[N][N];
int f[N][N], ans;
std::deque<std::pair<int, int> > Q;

#define innm(x, y) ((x) >= 1 && (x) <= n && (y) >= 1 && (y) <= m)

void work(int x, int y, int dx, int dy, int l) {
  Q.clear();
  for ( int L = 1; innm(x, y); ++L, x -= dx, y -= dy ) {
    if (!S[x][y]) Q.clear();
    else {
      while (!Q.empty() && L - Q.back().first + Q.back().second < f[x][y]) Q.pop_back();
      Q.push_back(std::make_pair(L, f[x][y]));
      if (Q.back().first - Q.front().first > l) Q.pop_front();
      if (!Q.empty()) f[x][y] = L - Q.front().first + Q.front().second;
      ans = std::max(ans, f[x][y]);
    }
  }
}

int main() {
  int sx, sy;
  n = R(), m = R(), sx = R(), sy = R(), K = R();
  rep(i, 1, n) {
    static char buf[N];
    scanf("%s", buf + 1);
    rep(j, 1, m)
      S[i][j] = buf[j] == '.',
      f[i][j] = -114514;
  }

  f[sx][sy] = 0;
  rep(i, 1, K) {
    static int s, t, d;
    s = R(), t = R(), d = R();
    int len = t - s + 1;
    switch(d) {
      case 1: rep(j, 1, m) work(n, j, 1, 0, len); break;
      case 2: rep(j, 1, m) work(1, j, -1, 0, len); break;
      case 3: rep(j, 1, n) work(j, m, 0, 1, len); break;
      case 4: rep(j, 1, n) work(j, 1, 0, -1, len); break;
    }
  }
  printf("%d\n", ans);
  return 0;
}