#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i <= b; ++i)
typedef long long LL;

LL f[10][10];

int main() {
  int a, b; LL k;
  scanf("%d%d%lld", &a,&b,&k);
  bool nmsl = 1;

  for (LL i = 1; i < k; ++i) {
    if (nmsl && f[a][b]) {
      nmsl = 0;
      k = (k-i) % (i-f[a][b]) + 1; i = 0;
      continue;
    }
    if (nmsl) f[a][b] = i;
    int c = a * b % 10;
    a = b; b = c;
  }
  printf("%d\n", a);
  return 0;
}
