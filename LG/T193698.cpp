#include <bits/stdc++.h>
using namespace std;

const int P = 1e9 + 7;
int a[200005], n, q, cn = 0;
#define fl fflush(stdout)

bool cnm(int x, int y) {
  printf("> %d %d\n", x, y); fl;
  int i; scanf("%d", &i);
  return !i;
}

int main() {
  scanf("%d%d", &n,&q);
  for (int i = 1; i <= n; ++i) a[i] = i;
  stable_sort(a + 1, a + 1 + n, cnm);
  int x, y;
  printf("? %d\n", a[1]); fl; scanf("%d", &x);
  printf("? %d\n", a[2]); fl; scanf("%d", &y);
  printf("! %d\n", ((y-x)%P+P)%P); fl;
  return 0;
}
