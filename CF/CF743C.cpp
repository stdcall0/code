#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; scanf("%d", &n);
  if (n <= 1) puts("-1");
  else printf("%d %d %d\n", n, n+1, n*n+n);
  return 0;
}
