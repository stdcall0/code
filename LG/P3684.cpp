#include <cstdio>
#include <cctype>
#include <algorithm>

const int maxN = 1005;

int n;
int a[maxN][maxN];

inline int fr() {
  int x = 0; char c;
  while (!isdigit(c = getchar()));
  x = c - '0';
  while (isdigit(c = getchar()))
    x = x * 10 + c - '0';
  return x;
}

namespace Helper { // I am the helper T cell
  char S[maxN][maxN];
  int col[maxN][maxN], row[maxN][maxN];
  int mx[maxN][maxN];

  inline bool rng(int x, int y) {
    return x >= 1 && y >= 1 && x <= n && y <= n;
  }
  inline bool chk(int x, int y, int sz) {
    int x1 = x-sz+1, y1 = y-sz+1,
        x2 = x+sz-1, y2 = y+sz-1;
    if (!rng(x1, y1) || !rng(x2, y2))
      return false;
    return mx[x2][y2] >= sz * 2 - 1;
  }
  inline void read() {
    n = fr();
    for (int i = 1; i <= n; ++i)
      scanf("%s", S[i] + 1);
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (S[i][j] == '.')
          row[i][j] = row[i][j - 1] + 1,
          col[i][j] = col[i - 1][j] + 1,
          mx[i][j] = std::min(std::min(row[i][j], col[i][j]), mx[i - 1][j - 1] + 1);
      }
    }
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
        if (S[i][j] == '.') {
          int L = 1, R = mx[i][j];
          while (L <= R) {
            int mid = L + R >> 1;
            if (chk(i, j, mid)) {
              a[i][j] = mid;
              L = mid + 1;
            } else
              R = mid - 1;
          }
        }
  }
};
namespace Solver {

  struct UnionSet {
    int fa[maxN * maxN], sz[maxN * maxN], f[maxN * maxN];

    inline void init(int x) {
      for (int i = 1; i <= x; ++i)
        fa[i] = i, sz[i] = 1;
    }

    inline int find(int x) {
      if (fa[x] != x)
        return find(fa[x]);
      return x;
    }

    inline bool merge(int x, int y, int v) {
      x = find(x), y = find(y);
      if (x != y) {
        if (sz[x] < sz[y])
          std::swap(x, y);
        fa[y] = x;
        f[y] = v;
        sz[x] += sz[y];
      }
      return x != y;
    }

    inline int get(int x, int y) {
      static int p1[maxN * 25], p2[maxN * 25];
      static int c1, c2;

      c1 = c2 = 0;
      for (int i = x; fa[i] != i; i = fa[i]) {
        p1[++c1] = i;
        if (fa[i] == y)
          return f[i];
      }
      for (int i = y; fa[i] != i; i = fa[i]) {
        p2[++c2] = i;
        if (fa[i] == x)
          return f[i];
      }

      while (p1[c1] == p2[c2])
        --c1, --c2;

      return std::min(f[p1[c1]], f[p2[c2]]);
    }
  } u;

  struct Edge {
    int x, y, v;

    bool operator< (const Edge &r) const {
      return v > r.v;
    }
  } G[maxN * maxN * 6];

  int cnt = 0;

  inline int c2i(int x, int y) {
    return (x - 1) * n + y;
  }

  inline void push(int x, int y) {
    static const int d[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    for (int D = 0; D < 4; ++D) {
      int p = x + d[D][0], q = y + d[D][1];
      if (Helper::rng(p, q) && a[p][q] >= a[x][y])
        G[++cnt] = {c2i(p, q), c2i(x, y), a[x][y]};
    }
  }

  inline void kruskal() {
    u.init(c2i(n, n));
    std::sort(G + 1, G + cnt + 1);
    for (int i = 1; i <= cnt; ++i)
      u.merge(G[i].x, G[i].y, G[i].v);
  }

  inline void build() {
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
        push(i, j);
    kruskal();
  }

  inline void queries() {
    int q;
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i) {
      static int x1, y1, x2, y2, c1, c2;
      x1 = fr(), y1 = fr(),
      x2 = fr(), y2 = fr();

      c1 = c2i(x1, y1),
      c2 = c2i(x2, y2);
      if (c1 == c2)
        printf("%d\n", std::max(0, a[x1][y1] * 2 - 1));
      else
        printf("%d\n", std::max(0, u.get(c1, c2) * 2 - 1));
    }
  }
};

int main() {
  Helper::read();
  Solver::build();
  Solver::queries();
  return 0;
}