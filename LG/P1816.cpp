#include <bits/stdc++.h>
using namespace std;

auto _r0 = ([]{ return ios :: sync_with_stdio(0), 0; })();

const int li = 22;
int a[100555][24];
int Lg[100555];

auto rmq_init = [&](int m) {
  Lg[1] = 0; Lg[2] = 1;
  for (int i=3; i<=m; i++) {
    Lg[i] = Lg[i/2] + 1;
  }

  for (int j=1; j<li; ++j) {
    for (int i=1; i + (1<<j) <= m+1; ++i) {
      a[i][j] = min(a[i][j-1], a[i + (1<<(j-1))][j - 1]);
    }
  }
};
auto rmq_query = [&](int x, int y) {
  int _ = Lg[y - x + 1];
  return min(a[x][_], a[y - (1 << _) + 1][_]);
};

int main() {
  int m, n;
  cin >> m >> n;
  for (int i=1; i<=m; i++) {
    cin >> a[i][0];
  }
  rmq_init(m); while (n--) {
    int x,y; cin >> x >> y;
    cout << rmq_query(x, y) << ' ';
  }
  return 0;
}