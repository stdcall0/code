#include <bits/stdc++.h>
using namespace std;

auto _r0 = ([]{ return ios :: sync_with_stdio(0), 0; })();
const int N = 1e5 + 5;
int n, q, a[N], c[N], b[N], L[N], R[N], m=0;

const int li = 22;
int mQ[100555][24];
int Lg[100555], lG=2;

auto rmq_init = [&](int m) {
  Lg[1] = 0; Lg[2] = 1;
  for (int i=lG+1; i<=m; i++) {
    Lg[i] = Lg[i/2] + 1;
  }
  lG = max(lG, m);

  for (int j=1; j<li; ++j) {
    for (int i=1; i + (1<<j) <= m+1; ++i) {
      mQ[i][j] = max(mQ[i][j-1], mQ[i + (1<<(j-1))][j - 1]);
    }
  }
};
auto rmq_query = [&](int x, int y) {
  int _ = Lg[y - x + 1];
  return max(mQ[x][_], mQ[y - (1 << _) + 1][_]);
};

int main() {
while ((cin >> n >> q) && n) {
  memset(a, 0, sizeof(a));
  memset(mQ, 0, sizeof(mQ));
  
  m = 0; for (int x,L=-13891431,i=1; i<=n; i++) {
    cin >> x;
    if (x != L) {
      a[++m] = L = x;
      c[m] = mQ[m][0] = 1;
      ::L[m] = i;
    } else ++c[m], ++mQ[m][0], R[m] = i;
    b[i] = m;
  }
  rmq_init(m);
  for (int x,y; q--; ) {
    cin >> x >> y;
    int p = b[x]; int pL = L[p], pR = R[p];
    int q = b[y]; int qL = L[q], qR = R[q];

    if (p == q) {
      cout << (y - x + 1) << endl;
    } else {
      int ans = max(pR - x + 1, y - qL + 1);
      if (p+1 <= q-1) ans = max(ans, rmq_query(p+1, q-1));
      cout << ans << endl;
    }
  }
}
  return 0;
}
