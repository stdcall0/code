#include <bits/stdc++.h>
using namespace std;

struct Solver {
  struct node {
    vector<int> idx;
    int child[26];
  } tr[10005];
  int alloc;
  vector<int> G[26];
  int rd[26], ans[26];
  Solver() : alloc(0) { }
  void put(const char* c, int ord, int cur = 0) {
    tr[cur].idx.push_back(ord);
    if (*c == '\0') return;
    int &x = tr[cur].child[*c - 'a'];
    if (!x) x = ++alloc;
    put(c + 1, ord, x);
  }
  void putcheck(const char* c, int ord, int cur = 0) {
    if (*c == '\0') {
      for (int i : tr[cur].idx)
        if (i < ord) { puts("NE"); exit(0); }
    } else putcheck(c + 1, ord, tr[cur].child[*c - 'a']);
  }
  void checkrange(int x) {
    auto &v = tr[x].idx;
    if (v.size() < 2) return;
    sort(v.begin(), v.end());
    for (int i=1; i<v.size(); ++i)
      if (v[i] != v[i-1] + 1) {
        puts("NE"); exit(0);
      }
  }
  void makemap(int cur = 0) {
    struct tmpnode { int ch, ord; };
    vector<tmpnode> v;
    for (int c = 0; c < 26; ++c) {
      int &x = tr[cur].child[c];
      if (x) {
        checkrange(x);
        v.push_back({c, tr[x].idx[0]});
      }
    }
    if (v.size() > 1) {
      sort(v.begin(), v.end(), [](const tmpnode& x, const tmpnode& y) { return x.ord < y.ord; });
      for (int i = 1; i < v.size(); ++i) {
        G[v[i-1].ch].push_back(v[i].ch), ++rd[v[i].ch];
      }
    }
    for (int c = 0; c < 26; ++c) if (tr[cur].child[c]) makemap(tr[cur].child[c]);
  }
  void deduce() {
    deque<int> Q;
    for (int i = 0; i < 26; ++i) if (rd[i] == 0) Q.push_back(i);
    if (Q.empty()) { puts("NE"); exit(0); }
    int idx = 0;
    while (!Q.empty()) {
      int x = Q.front(); Q.pop_front();
      ans[x] = idx++;
      for (int y : G[x]) {
        --rd[y];
        if (rd[y] == 0) Q.push_back(y);
      }
    }
    for (int i = 0; i < 26; ++i) if (rd[i]) { puts("NE"); exit(0); }
    puts("DA");
    for (int i = 0; i < 26; ++i) printf("%c", ans[i] + 'a');
    puts("");
  }
} T;

char s[105][105];

int cnm[105];

int main() {
  int n; scanf("%d", &n);
  for (int i = 1; i <= n; ++i) scanf("%s", s[i]);
  for (int i = 1; i <= n; ++i) { static int o; scanf("%d", &o); cnm[o] = i; }
  for (int i = 1; i <= n; ++i) T.put(s[i], cnm[i]);
  for (int i = 1; i <= n; ++i) T.putcheck(s[i], cnm[i]);
  T.makemap(); T.deduce();
  return 0;
}
