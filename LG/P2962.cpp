#include<bits/stdc++.h>
#define Rn(a,n)a+1,a+n+1
#define Edge(T,x,y)T[x].push_back(y);T[y].push_back(x)
#define rep(i,l,r)for(int i=(l),_r_R=(r);i<=_r_R;++i)
typedef long long ll;typedef long double ld;typedef unsigned long long ull;inline ll Rl(){ll ret(0);int c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}inline int R(){int ret(0),c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}

int n, m;
bool P[37][37];
int v[37];

inline void fil(int x, int y) {
  // ADD row x to row y
  rep(i, 0, n) P[y][i] ^= P[x][i];
}
bool G(int col) {
  if (col == n) {
    if (P[n][n] == 0) assert(P[n][0] == 0);
    return P[n][n] != 0;
  }
  // select a master row
  bool sta = 0;
  rep(i, col, n) if (P[i][col]) {
    if (i != col) std::swap(P[i], P[col]);
    sta = 1; break;
  }
  if (!sta) return G(col + 1), false;
  rep(i, col + 1, n)
    if (P[i][col]) fil(col, i);
  return G(col + 1);
}
inline int subcalc(int i) {
  if (P[i][i] != 0) {
    bool left = 0;
    rep(j, i + 1, n) if (P[i][j]) left ^= v[j];
    return v[i] = left != P[i][0];
  } else return -1;
}
inline int calc() {
  int res = 0;
  for (int i = n; i >= 1; --i) {
    subcalc(i);
    res += v[i];
  }
  return res;
}
int ans = 1145141919;
void dfs(int x, int v = 0) {
  if (v >= ans) return;
  if (x == 0) { ans = v; return; }
  int vi = subcalc(x);
  if (vi != -1) dfs(x - 1, v + vi);
  else {
    ::v[x] = 0; dfs(x - 1, v);
    ::v[x] = 1; dfs(x - 1, v + 1);
  }
}
inline void print() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      printf("%d ", P[i][j]);
    }
    printf("%d\n", P[i][0]);
  }
}

int main() {
  n = R(); m = R();
  rep(i, 1, n) P[i][0] = 1, P[i][i] = 1; // RES -> 1
  rep(i, 1, m) {
    static int x, y; x = R(), y = R();
    P[x][y] = 1; P[y][x] = 1;
  }
  // print(); printf("---\n");
  if (G(1)) {
    // print();
    // Gauss ok, no free var
    printf("%d\n", calc());
  } else {
    // print();
    dfs(n);
    printf("%d\n", ans);
  }
  return 0;
}