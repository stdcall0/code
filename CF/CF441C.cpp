#include <bits/stdc++.h>
using namespace std;

int n, m, k;

int main() {
  scanf("%d%d%d", &n,&m,&k);
  int x=1, y=1, det=1, rm = n*m;
  auto _=[&](){
    y += det;
    if (y<1||y>m) {
      ++x; det=-det;
      y += det;
    }
    --rm;
  };
  while (k--) {
    int v = k ? 2 : rm;
    printf("%d ", v);
    for (int i=1; i<=v; ++i) {
      printf("%d %d ", x, y);
      _();
    }
    puts("");
  }
  return 0;
}
