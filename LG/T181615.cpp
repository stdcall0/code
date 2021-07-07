#include <bits/stdc++.h>
using namespace std;

typedef uint64_t ull;

void guess() {
    int mid, L = 1, R = 64, reply;
    ull val;
    while (L < R) {
      mid = L + R + 1 >> 1;
      val = (ull)1 << (mid - 1);
      printf("%llu\n", val); fflush(stdout);
      scanf("%d", &reply);
      if (reply == 0) return;
      if (reply == 1) R = mid - 1;
      else L = mid;
    }
    // printf("BIT: %d\n", L);
    if (L == 1) {
      printf("1\n"); fflush(stdout);
      scanf("%d", &reply);
      assert(reply == 0);
      return;
    }
    ull re = (ull)1 << (L - 1);
    for (int i = L - 2; i >= 0; i--) {
      val = (ull)1 << i;
      printf("%llu\n", re + val); fflush(stdout);

      scanf("%d", &reply);
      if (reply == 0) return;
      if (reply == -1) re += val;
    }
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    guess();
  }
  return 0;
}
