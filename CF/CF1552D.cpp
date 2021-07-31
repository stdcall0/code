#include <cstdio>

int main() {
  int t; scanf("%d", &t);
  while (t--) {
    static int a[15], n, sta; scanf("%d", &n);
    sta = 1;
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &a[i]); sta *= 3;
    }
    bool ok = 0;
    for (int i = 0; i < sta - 1; ++i) {
      int x = i, res = 0;
      for (int j = 1; j <= n; ++j) { 
        int bi = x % 3;
        if (bi != 2) res += bi ? a[j] : -a[j];
        x /= 3;
      }
      if (!res) { ok = 1; break; }
    }
    puts(ok ? "YES" : "NO");
  }
  return 0;
}