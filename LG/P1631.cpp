#include <bits/stdc++.h>
using namespace std;

auto _r0 = ([]{ return ios :: sync_with_stdio(0), 0; })();

const int N = 1e5 + 5;
int n, a[N], b[N];

struct node {
  int x, y;
  inline int v() const { return x + b[y]; }
  inline node T() const { return {x, y+1}; }
  bool operator< (const node &r) const { return v() > r.v(); }
};
priority_queue<node> Q;

int main() {
  cin >> n;
  for (int i=1; i<=n; i++) {
    cin >> a[i];
    Q.push({a[i], 1});
  }
  for (int i=1; i<=n; i++) cin >> b[i];
  for (int i=1; i<=n; i++) {
    printf("%d ", Q.top().v());
    node nw = Q.top().T();
    Q.pop();
    if (nw.y <= n) {
      Q.push(nw);
    }
  }
  return 0;
}
