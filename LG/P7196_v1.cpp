#include <cstdio>
#include <vector>
#include <algorithm>

struct D { // Direction
  int i;
  static constexpr int d[4][2] = {
    {0, 1}, {1, 0},
    {0, -1}, {-1, 0}
  };
  static constexpr int g[4] = {
    1, 2, 3, 0
  };
  inline D left() const {
    return {(i + 1) % 4};
  }
  inline D right() const {
    return {(i + 3) % 4};
  }
  inline bool msk(int mask) const {
    return mask >> g[i] & 1;
  }
};
const D north{3}, east{0}, south{1}, west{2};
const D all[4] = {north, east, south, west};
struct P { // Position
  int x, y;
  inline P go(const D &d) const {
    return {x + D::d[d.i][0], y + D::d[d.i][1]};
  }
  inline int dis(int p, int q) const {
    return (x - p) * (x - p) + (y - q) * (y - q);
  }
};

int n, m, dL, dR, lim;
int G[55][55]; // Tube Maskes
int wt[105], wk[105], wx[105], wy[105], wc, wid[105];

bool cmp(int x, int y) {
  return wt[x] < wt[y];
}

struct E { // Mouse Entity
  D d;
  bool sex; // 0 - male, 1 - female
  int count; // times meet with 3cross
  int state; // state no, 0 - mature, 1 - pregnated, 2 - aftersex, 3 - child
  int delay; // state delay
  int frozen; // frozen time
  static E gen(D dd) {
    return {dd, !(dd.i & 1), 0, 0, 5};
  }
};

// Event Runner
int sta[55][55]; // 0 - normal, 1 - kill, 2 - sex invert
int fc[55][55]; // frozen count
int mc = 0;
std::vector<E> a[2][55][55];
bool c = 0;
inline void tick(int x, int y) {
  auto &A = a[c][x][y];
  int M = G[x][y];
  if (A.size() == 0)
    return;
  printf("Ticking: (%d,%d) %d mice\n",x,y,A.size());
  if (sta[x][y] == 1) // kill
    return;
  if (A.size() == 2 && A[0].sex ^ A[1].sex) {
    if (!(A[0].state | A[1].state | A[0].delay | A[1].delay)) {
      A[0].state = A[1].state = 1;
      A[0].delay = A[1].delay = 2;
    }
  }
  bool born = false;
  for (auto &v : A) {
    if (sta[x][y] == 2)
      v.sex = !v.sex;
    v.frozen += fc[x][y] * 3;

    if (v.state == 1 && v.delay == 0)
      v.state = 2, v.delay = 1,
      born = true;
    if (v.state == 3 && v.delay == 0)
      v.state = 0;
    printf("Mouse at (%d,%d) state %d delay %d frozen %d\n", x,y,v.state,v.delay,v.frozen);
  }
  if (born) for (const D &d : all)
    if (d.msk(M))
      A.push_back(E::gen(d));

  P now = {x, y};
  for (auto &e : A) {
    ++mc;
    if (e.frozen > 0) {
      --e.frozen;
      a[!c][x][y].push_back(e);
      continue;
    }
    if (e.delay > 0)
      --e.delay;
    if (e.state == 0 || e.state == 3) {
      if (!e.d.msk(M)) {
        bool L = e.d.left().msk(M);
        bool R = e.d.right().msk(M);
        if (L && R) {
          ++e.count;
          if (e.count & 1) e.d = e.d.left();
          else e.d = e.d.right();
        } else {
          if (L)
            e.d = e.d.left();
          else
            e.d = e.d.right();
        }
        a[!c][x][y].push_back(e);
      } else {
        P then = now.go(e.d);
        a[!c][then.x][then.y].push_back(e);
      }
    } else {
      a[!c][x][y].push_back(e);
    }
  }
}
inline D c2d(char c) {
  if (c == 'E') return east;
  else if (c == 'N') return north;
  else if (c == 'W') return west;
  else return south;
}

int main() {
  scanf("%d%d%d%d", &dL, &dR, &n, &m);
  dR = dR * dR;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      scanf("%d", &G[i][j]);
  int k; scanf("%d", &k);
  while (k--) {
    static int x,y;
    static char dd[3], sex[3];
    scanf("%d%d%s%s", &x,&y,dd,sex);
    a[0][x][y].push_back({c2d(dd[0]), sex[0]=='Y', 0, 0, 0, 0});
  }
  scanf("%d%d", &wc, &lim);
  for (int i = 1; i <= wc; ++i) {
    scanf("%d%d%d%d", &wk[i], &wt[i], &wx[i], &wy[i]);
    if (wk[i] == 3) wt[i] += 3;
    wid[i] = i;
  }
  std::sort(wid + 1, wid + 1 + wc, cmp);
  int tic, wi = 1, tim = 0;
  scanf("%d", &tic);
  while (tim < tic) {
    while (wi <= wc && wt[wid[wi]] <= tim) {
      k = wid[wi];
      if (wk[k] == 3) sta[wx[k]][wy[k]] = 1;
      else if (wk[k] == 4) sta[wx[k]][wy[k]] = 2;
      else if (wk[k] == 1) {
        P p;
        sta[wx[k]][wy[k]] = 1;
        for (const auto &d : all) {
          p = {wx[k], wy[k]};
          int rem = dL;
          while (rem > 0 && d.msk(G[p.x][p.y])) {
            p.go(d);
            sta[p.x][p.y] = 1;
            --rem;
          }
        }
      } else {
        P p{wx[k], wy[k]};
        for (int i = 1; i <= n; ++i)
          for (int j = 1; j <= m; ++j)
            if (p.dis(i, j) <= dR)
              ++fc[i][j];
      }
      ++wi;
    }
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j) {
        a[!c][i][j].clear();
      }
    mc = 0;
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j) {
        tick(i, j);
        sta[i][j] = fc[i][j] = 0;
      }
    c = !c;
    if (mc > lim) {
      puts("-1");
      return 0;
    }
    printf("Tick %d: total %d\n", tim, mc);
    ++tim;
  }
  printf("%d\n", mc);
  return 0;
}
