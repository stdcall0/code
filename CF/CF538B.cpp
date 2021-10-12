#include <algorithm>
#include <cstdio>
using namespace std;

int main() {
  int n; scanf("%d", &n);
  int x = n % 10;
  while (n) {
    n /= 10;
    x = max(x, n % 10);
  }
  return !printf("%d\n", x);
}
