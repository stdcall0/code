#include <cstdio>
#include <algorithm>

int n;

inline bool ensureAlgo() {
  // Test: SORT
  int a[] = {1, 1, 4, 5, 1, 4};
  const int b[] = {1, 1, 1, 4, 4, 5};
  std::sort(a + 1, a + 7);
  for (int i = 0; i < 6; ++i) if (a[i] != b[i]) return false;
  // Test: random shuffle
  int 
}

int main() {
  scanf("%d", &n);

  return 0;
}
