#include <bits/stdc++.h>
using namespace std;

int n;
int M[5][10];

inline bool eliminate() {
  bool _ = 0;
  static int f[5][10];
  memset(f, 0, sizeof(f));
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 7; ++j) if (f[i][j] == 0 && M[i][j]) {
      int I = i, J = j;
      while (I < 5 && M[i][j] == M[I][j]) f[I][j] = 1, ++I;
      while (J < 7 && M[i][j] == M[i][J]) f[i][J] = 1, ++J;
      if (I - i > 2) for (int k = i; k < I; ++k) f[k][j] = 2;
      if (J - j > 2) for (int k = j; k < J; ++k) f[i][k] = 2;
    } else break;
  }
  for (int i = 0; i < 5; ++i)
    for (int j = 0; j < 7; ++j) {
      if (f[i][j] == 2) M[i][j] = 0, _ = 1;
    }
  return _;
}
inline bool physics() {
  bool _ = 0;
  for (int i = 0; i < 5; ++i) {
    static int buf[10];
    memset(buf, 0, sizeof(buf));
    int idx = -1, mx = 0;
    for (int j = 0; j < 7; ++j) {
      if (M[i][j]) mx = j, buf[++idx] = M[i][j];
    }
    if (idx != mx) memcpy(M[i], buf, sizeof(M[i])), _ = 1;
  }
  return _;
}
inline bool update() {
  physics();
  while (eliminate()) {
    if (!physics()) break;
  }
  bool _ = 1; for (int i = 0; i < 5; ++i) if (M[i][0]) _ = 0;
  return _;
}
void dfs(int x) {
  if (x == n + 1) return;
  
}

int main() {
  scanf("%d", &n);
  for(int i=0;i<5;++i)for(int x=1,j=0;x;++j)scanf("%d",&x),M[i][j]=x;

  return 0;
}
