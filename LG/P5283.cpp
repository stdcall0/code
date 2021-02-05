#include <bits/stdc++.h>
using namespace std;
#define NDEBUG

auto _r0 = ([]{ return ios :: sync_with_stdio(0), 0; })();

typedef long long ll;
const int N = 5e5 + 5;
const int depth = 31;
int n, k;
ll a[N], s[N];

namespace Trie {
  int ac;
  struct node {
    int dep, s[2], siz;
  } pool[(int)5e7 + 5];

  inline int newNode(int x) { pool[++ac] = {pool[x].dep + 1, {0, 0}, 0}; return ac; }

  void insert(int x, ll v) {
    node &y = pool[x];
    if (y.dep <= depth) {
      int & z = y.s[v & 1LL];
      z = z ? z : newNode(x);
      insert(z, v >> 1LL);
    }
    ++y.siz;
  }

  ll query(int x, ll v, int rank) {
    ll res = 0;
    for (; pool[x].dep <= depth; ) {
      bool q = v & 1LL; bool w = !q;
      int g = pool[x].s[w], h = pool[x].s[q];
      res <<= 1LL;
      if (!g) assert(h), x = h;
      else {
        int subsize = pool[g].siz;

        if (rank <= subsize) x = g, res |= 1LL;
        else assert(h), x = h, rank -= subsize;
      }

      v >>= 1LL;
    }
    return res;
  }

  struct revision {
    int root;
    inline void ins(ll x) { insert(root, x); }
    inline ll qry(ll v, int rank) { return query(root, v, rank); }
  } *c;

  inline void b() {
    static revision R = {1}; c = &R;
    pool[0] = pool[ac = 1] = {0, {0, 0}, 0};
  }
};
namespace Utils {
  inline ll len(ll x) {
    ll r = 0;
    for (; x >>= 1LL;) ++r;
    return r;
  }
  inline ll rev(ll x) {
    ll r = 0;
    for (int i=depth + 1; i--; x >>= 1LL) {
      r = (r << 1LL) | (x & 1LL);
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
namespace Heaper {
  struct node {
    ll v;
    int x, rank;
    bool operator< (const node &r) const {
      return v < r.v;
    }
  };
  priority_queue<node> Q;

  struct queuemanager {
    typedef const queuemanager * const ret;
    inline ret add(const node &r) const {
      if (r.v < 0) return this;
      Q.push(r); return this;
    }
    inline ret get(node &r) const { r = Q.top(); return this; }
    inline ret pop(node &r) const { get(r); Q.pop(); return this; }
    inline ret nxt(node &r) const {
      using Trie::c;
      if (++r.rank <= n) r.v = c->qry(s[r.x], r.rank);
      else r.v = -1;
      return this;
    }
  } *q;
  inline void b() { static queuemanager Q; q = &Q; }
};

int main() {
  using Trie::c;
  using Heaper::q;
  using Utils::rev;

  cin >> n >> k;

  Trie::b(); Heaper::b();
  c->ins(s[0] = 0);

  ll x; for (int i=1; i<=n; i++) {
    cin >> x; s[i] = s[i-1] ^ x;
    c->ins(rev(s[i]));
  }
  for (int i=1; i<=n; i++) s[i] = rev(s[i]);

  // Stage 1: Calculate max value of all nodes
  for (int i=0; i<=n; i++) {
    // { v, x, rank }
    q->add({ c->qry(s[i], 1), i , 1 });
  }

  // Stage 2: Calculate first 2k values
  ll res = 0;
  for (k <<= 1; k--; ) {
    Heaper::node t;
    q -> pop(t);
    res += t.v;
    q -> nxt(t) -> add(t);
  }

  cout << (res >> 1) << endl;
  return 0;
}
