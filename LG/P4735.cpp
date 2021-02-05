#include <bits/stdc++.h>
using namespace std;
#define NDEBUG

auto _r0 = ([]{ return ios :: sync_with_stdio(0), 0; })();

const int N = 3e5 + 5;
int n, a[N], depth;

namespace Trie {
  int ac, rc;
  struct node {
    int dep, s[2], lst;
  } pool[(int)3e7 + 5];

  inline int clone(int x) { pool[++ac] = pool[x]; return ac; }

  int insert(int x, int v, int rid) {
    int r = clone(x);
    node &y = pool[r];
    y.lst = max(y.lst, rid);
    if (y.dep <= depth) {
      if (y.s[v & 1]) y.s[v & 1] = insert(y.s[v & 1], v >> 1, rid);
      else {
        pool[0] = {y.dep + 1, {0, 0}};
        y.s[v & 1] = insert(0, v >> 1, rid); // so it would clone pool[0] as a new node
      }
    }
    return r;
  }

  int query(int x, int v, int L) {
    int res = 0;
    for (; pool[x].dep <= depth; ) {
      bool q = v & 1, w = 1 - q;
      res <<= 1;
      if (pool[x].s[w] && pool[pool[x].s[w]].lst >= L) {
        x = pool[x].s[w];
        res |= 1;
      } else {
        x = pool[x].s[q];
      }
      v >>= 1;
    }
    return res;
  }

  struct revision {
    int root;
    inline void ins(int);
    inline int qry(int v, int L) { return query(root, v, L); }
  } rev[N * 4], *c;

  inline void revision::ins(int x) {
    ++rc; rev[rc] = {insert(root, x, rc-1)};
    c = &rev[rc];
  }

  inline void b() { pool[0] = pool[rev[rc = 1].root = ac = 1] = {0, {0, 0}}; c = &rev[1]; }
};
namespace Utils {
  inline int len(int x) {
    int r=0;
    for (; x >>= 1;) ++r;
    return r;
  }
  inline int rev(int x) {
    int r = 0;
    for (int i=depth + 1; i--; x >>= 1) {
      r = (r << 1) | (x & 1);
    }
    return r;
  }
  void bits(void const * const ptr) {
    for (int i=3; i>=0; i--) {
      for (int j=7; j>=0; j--) {
        printf("%u", (((unsigned char*) ptr)[i] >> j) & 1);
      }
    }
    puts("");
  }
};

int main() {
  int m, _(0);
  cin >> n >> m;
  depth = 30;
  Trie::b();
  Trie::c->ins(0);
  for (int x,i=1; i<=n; i++) {
    cin >> x;
    Trie::c->ins(Utils::rev(_ ^= x));
  }
  int l, r, x;
  for (char O[5]; m--; ) {
    cin >> O;
    if (O[0] == 'A') {
      cin >> x;
      Trie::c->ins(Utils::rev(_ ^= x));
    } else {
      cin >> l >> r >> x;
      cout << Trie::rev[r+1].qry(Utils::rev(_ ^ x), l) << endl;
    }
  }
  return 0;
}
