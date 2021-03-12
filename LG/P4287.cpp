#include <bits/stdc++.h>
using namespace std;

#define Rn(a, n) a + 1, a + n + 1
typedef long long ll;
typedef unsigned long long ull;
const int N = 5e5 + 5;
// const ull bs = 233;

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

int n;
char s[N * 11];
int p[N * 11], ans = 0;
/*
ull pw[N], h1[N], h2[N]; // h2 rev-ed

inline ull get(int in, int x, int y) {
  if (in == 1) return h1[y] - h1[x-1] * pw[y-x+1];
  if (in == 2) return h2[x] - h2[y+1] * pw[y-x+1];
  assert( !"in must be either 1 or 2" );
}
inline bool check(int mid, int l) {
  // check, if
  // w == [mid-l*2+1, mid-l] == [mid+1, mid+l]
  // wR == [mid-l+1, mid] == [mid+l+1, mid+l*2]
  return
      get(1, mid - l*2 + 1, mid - l) == get(1, mid + 1, mid + l)
    && get(1, mid - l + 1, mid) == get(1, mid + l + 1, mid + l*2)
    && get(1, mid+1, mid+l) == get(2, mid-l+1, mid);
}
*/

void manacher(int n = ::n * 2 + 1) {
  for (int c=0, mx=0, i=1; i<=n; ++i) {
    p[i] = i < mx ? min(p[c * 2 - i], mx - i) : 1;
    while (s[p[i] + i] == s[i - p[i]]) ++p[i];
    if (p[i] + i > mx) {
      if (i & 1) {
        for (int j=max(mx, i+4); j < i+p[i]; ++j) {
          if (!(j-i & 3) && p[i - (j-i)/2] > (j-i)/2) {
            ans = max(ans, j - i);
          }
        }
      }
      mx = p[i] + i; c = i;
    }
  }
}

int main() {
  scanf("%d%s", &n, s + 1);
  assert( n == strlen(s + 1) );
  for (int i=n; i; i--) {
    s[i * 2 + 1] = '#';
    s[i * 2] = s[i];
  }
  s[1] = '#';
  manacher(); printf("%d\n", ans);
  return 0;
}
