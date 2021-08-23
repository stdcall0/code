#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i <= b; ++i)
typedef long long LL;

int n, zec = 0;
vector<int> pos, neg;

int main() {
  LL sum = 0;
  scanf("%d", &n);
  rep(i, 1, n) {
    int x; scanf("%d", &x); sum += x;
    if (x == 0) ++zec;
    else if ((x < 0) ^ (x & 1)) neg.push_back(abs(x));
    else pos.push_back(abs(x));
  }
  sort(neg.begin(), neg.end(), greater<int>());
  sort(pos.begin(), pos.end(), greater<int>());
  decltype(pos)::iterator ln = neg.begin(), lp = pos.begin(), rn = neg.end(), rp = pos.end();
  for (int i = 1; i <= n; ++i) {
    if (i & 1) {
      if (lp < rp) sum += 1LL * (n - i) * *(lp++);
      else if (zec) --zec;
      else sum -= 1LL * (n - i) * *(--rn);
    } else {
      if (ln < rn) sum += 1LL * (n - i) * *(ln++);
      else if (zec) --zec;
      else sum -= 1LL * (n - i) * *(--rp);
    }
  }
  printf("%lld\n", sum);
  return 0;
}
