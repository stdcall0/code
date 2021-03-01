struct UnionSet {
  const static int N = 1e5 + 5;
  int fa[N], siz[N], n;
  inline void reset() { for (int i=1; i<=n; i++) fa[i] = i, siz[i] = 1; }
  inline void resize(int nn) { n = nn; reset(); }
  inline int get(int x) {
    if (fa[x] != x) return fa[x] = get(fa[x]);
    return x;
  }
  inline bool together(int x, int y) {
    x = get(x), y = get(y);
    if (x == y) return false;
    if (siz[x] > siz[y]) {
      siz[x] += siz[y];
      return fa[y] = x;
    } else {
      siz[y] += siz[x];
      return fa[x] = y;
    }
  }
  inline bool same(int x, int y) {
    x = get(x), y = get(y);
    return x == y;
  }
};
