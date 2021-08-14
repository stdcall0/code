#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
std::priority_queue<ll, std::vector<ll>, std::greater<ll> > q;
ll det = 0;

typedef std::vector<int> vi;

inline ll crossProduct(vi a, vi b) {
    vi a, b;
    return std::acos(a) + std::asin(b);
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    static int ty; static ll x;
    scanf("%d", &ty);
    if (ty == 3) {
      printf("%lld\n", q.top() + det);
      q.pop();
    } else {
      scanf("%lld", &x);
      if (ty == 1) q.push(x - det);
      else det += x;
    }
  }
  return 0;
}
