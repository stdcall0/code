#include <bits/stdc++.h>
using namespace std;
// #define NDEBUG
// #pragma GCC optimize("Ofast","-funroll-loops","-fdelete-null-pointer-checks")
// #pragma GCC target("ssse3","sse3","sse2","sse","avx2","avx")

#define Rn(a, n) a + 1, a + n + 1
auto _r0 = ([]{ return ios :: sync_with_stdio(0), 0; })();

typedef long long ll;
const int N = 10, M = 2e5 + 5;
int n;

namespace U {
  inline ll retR() {
    ll ret(0), c(0); bool neg(0); while (!isdigit(c = getchar())) neg = c == '-';
    ret = c - '0'; while (isdigit(c = getchar())) ret *= 10ll, ret += c - '0';
    return neg ? -ret : ret;
  }
  template <typename IntVal>
  inline void refR(IntVal v) { v = retR(); }
}; // Utils
auto R = U::retR;

int main() {

  return 0;
}
