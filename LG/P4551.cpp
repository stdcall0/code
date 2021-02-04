#include <bits/stdc++.h>
using namespace std;
#define NDEBUG

auto _r0 = ([]{ return ios :: sync_with_stdio(0), 0; })();

const int N = 1e5 + 5;
int n, a[N];

namespace Graph {
  int hed[N];
  struct edge {
    int to, nxt, v; } edges[N * 2];
  inline void __addedge(int x, int y, int v) {
    static int cnt = 0;
    edges[++cnt] = {y, hed[x], v};
    hed[x] = cnt;
  }
  void dfs(int x, int fa) {
    for (int e=hed[x]; e; e=edges[e].nxt) {
      int y=edges[e].to;
      if (y != fa) {
        a[y] = a[x] ^ edges[e].v;
        dfs(y, x);
      }
    }
  }
  inline void Edge(int x, int y, int v) {
    __addedge(x, y, v); __addedge(y, x, v);
  }
};
namespace Fucking_Trie { // need to reverse before putting into Trie
  int depth;         // trie depth
  struct node {
    int dep;         // node depth
    int s[2];        // son id
  } pool[N * 31 + 5];
  int ac;           // node count
  inline int firstv(const int &v) {
    return v & 1;   // we've reversed the fucking elemento
  }
  inline int otherv(const int &v) {
    return v >> 1;  // we've reversed the fucking elemento
  }

  void inserto(node &x, int v) {
    // printf("Inserting: depNode %d, firstV %d, otherV %d\n", x.dep, firstv(v), otherv(v));
    if (x.dep <= depth) {
      if (x.s[firstv(v)]) inserto(pool[x.s[firstv(v)]], otherv(v));
      else {
        pool[x.s[firstv(v)] = ++ac] = {x.dep + 1, {0, 0}};
        inserto(pool[ac], otherv(v));
      }
    }
  }
  inline void ins(int v) {
    static bool inited = false;
    if (!inited) {
      inserto(pool[ac = 0] = {0, {0, 0}}, v);
      inited = 1;
    } else {
      inserto(pool[0], v);
    }
  }
  inline int queryo(int v) {
    int res = 0;
    for (int x=0; pool[x].dep <= depth; ) {
      bool w = !firstv(v), q= 1-w;
      res <<= 1;
      if (pool[x].s[w]) {
        x = pool[x].s[w];
        res |= 1;
      } else {
        assert(pool[x].s[q]);
        x = pool[x].s[q];
      }
      v = otherv(v);
    }
    return res;
  }
};
namespace Utils {
  inline int len(int x) {
    int r=0;
    for (; x >>= 1;) ++r;
    return r;
  }
  inline int rev(int x) {
    using Fucking_Trie::depth;
    int r = 0;
    for (int i=depth+1; i--; x >>= 1) {
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
  cin >> n;
  for (int x,y,z,i=1; i<n; i++) {
    cin >> x >> y >> z;
    Graph::Edge(x, y, z);
  }
  Graph::dfs(1, 0);
  Fucking_Trie::depth = Utils::len(*max_element(a+1, a+1+n));
  // printf("Depth: %d\n", Fucking_Trie::depth);
  for (int i=1; i<=n; i++) {
    a[i] = Utils::rev(a[i]);
#ifndef NDEBUG
    printf("A[%d]: ", i); Utils::bits(&a[i]);
#endif
    Fucking_Trie::ins(a[i]);
  }
  int r=0; for (int i=1; i<=n; i++) {
    r = max(r, Fucking_Trie::queryo(a[i]));
  }
  cout << r << endl;
  // printf("FINAL: ac = %d , acceled = %d\n", Fucking_Trie::ac, (N*31)+5);
  return 0;
}
