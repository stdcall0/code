#include <cstdio>
#include <algorithm>
#include <vector>

// N E S W
const int offset[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
int n, m;

struct Pos { int x, y; };
struct D { // orientations
  int i;
  D(int i = 0) : i(i) { }
  D(char c) {
    if (c == 'N') i = 0;
    else if (c == 'E') i = 1;
    else if (c == 'S') i = 2;
    else i = 3;
  }
  inline D left() const { return {(i + 1) % 4}; }
  inline D right() const { return {(i + 3) % 4}; }
  inline Pos move(Pos c) const {
    return {c.x + offset[i][0], c.y + offset[i][1]};
  }
  inline bool chk(int x, int y) const {
    int p = x + offset[i][0], q = y + offset[i][1];
    if (p < 1 || q < 1 || p > n || q > m) return true;
    return false;
  }
  inline bool mask(int msk) const {
    return msk >> i & 1;
  }
};

const D dN = {0}, dE = {1}, dS = {2}, dW = {3};
const D dAll[4] = {dN, dE, dS, dW};
inline int fix(int mask, int x, int y) {
  for (int i = 0; i < 4; ++i) {
    if (dAll[i].chk(x, y))
      mask = (mask | (1 << i)) ^ (1 << i);
  }
  return mask;
}

struct Entity {
  D d;
  bool preg;
  int sex, breed, frozen, count, age;
  Entity(D d, char g, bool m = true) : d(d), sex(g == 'X'), preg(0), age(m ? 0 : 5), breed(0), frozen(0), count(0) {}
  inline bool move(int mask) {
    if (d.mask(mask)) return true;
    bool L = d.left().mask(mask), R = d.right().mask(mask);
    if (L && R) {
      if (++count & 1) d = d.left();
      else d = d.right();
    } else {
      if (L) d = d.left();
      else d = d.right();
    }
    return false;
  }
};

enum WepType {
  OneShot, AreaKill, AreaFreeze, GenderToggle
};
enum WepEffect {
  Kill, Freeze, Gender
};
const WepType wt[4] = {AreaKill, AreaFreeze, OneShot, GenderToggle};
const WepEffect we[4] = {Kill, Kill, Freeze, Gender};
int dL, dR;
int aN[55][55], aE[55][55], aW[55][55], aS[55][55];
struct Weapon {
  WepType t;
  int x, y;
  Weapon(int T, int x, int y) : t(wt[T - 1]), x(x), y(y) { }
  inline bool on(int p, int q) const {
    if (t == AreaKill) {
      int v1, v2;
      if (x == p) {
        v1 = std::abs(y - q);
        if (y < q) v2 = aE[x][y];
        else v2 = aW[x][y];
      } else {
        if (y != q) return false;
        v1 = std::abs(x - p);
        if (x < p) v2 = aS[x][y];
        else v2 = aN[x][y];
      }
      v2 = std::min(v2, dL);
      return v1 <= v2;
    } else if (t == AreaFreeze)
      return (x - p) * (x - p) + (y - q) * (y - q) <= dR;
    else
      return x == p && y == q;
  }
  inline WepEffect get() const { return we[(int)t]; }
};

std::vector<Entity> map[2][55][55];
std::vector<Weapon> wep[1005];
int ne, nw, lim, tm;
int G2[55][55], G[55][55], t = 0, c = 0, cnt = 0;

inline void tick() {
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      map[!c][i][j].clear();
  cnt = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) if (map[c][i][j].size()) {
      int freeze = 0;
      bool gender = 0, skip = 0, born = 0;
      auto & M = map[c][i][j];
      for (auto &v : wep[t])
        if (v.on(i, j)) {
          if (v.get() == Kill)
            skip = true;
          else if (v.get() == Freeze)
            freeze += 3;
          else
            gender ^= 1;
        }
      if (!skip) {
        for (auto &v : M) {
          v.frozen += freeze;
          if (gender) v.sex ^= 1;
          if (v.preg && v.breed == 0) {
            born = true;
            v.preg = false;
          }
        }
        if (born)
          for (auto d : dAll) if (d.mask(G[i][j])) {
            M.push_back(Entity(d, (d.i & 1) ? 'X' : 'Y', false));
          }
#define ze(x) ((M[0].x) == 0 && (M[1].x) == 0)
        if (M.size() == 2 && M[0].sex ^ M[1].sex && ze(preg) && ze(frozen) && M[0].age >= 5 && M[1].age >= 5) {
          M[0].preg = M[1].preg = true;
          M[0].breed = M[1].breed = 2;
          M[0].frozen = M[1].frozen = 3;
        }
        Pos p = {i, j};
// int sex, breed, frozen, count, age; bool preg;
        for (auto &v: M) {
          Pos np = {i, j};
          if (v.frozen == 0) {
            ++v.age;
            bool flag = v.move(G2[i][j]);
            if (flag) np = v.d.move(p);
          } else {
            --v.frozen;
            if (v.breed) --v.breed;
          }
          map[!c][np.x][np.y].push_back(v);
          ++cnt;
        }
      }
    }
  c = !c;
}

int main() {
  scanf("%d%d%d%d", &dL, &dR, &n, &m);
  dR = dR * dR;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &G[i][j]);
      G2[i][j] = fix(G[i][j], i, j);
      if (dN.mask(G2[i][j])) aN[i][j] = aN[i - 1][j] + 1;
      if (dW.mask(G2[i][j])) aW[i][j] = aW[i][j - 1] + 1;
    }
  for (int i = n; i >= 1; --i)
    for (int j = m; j >= 1; --j) {
      if (dE.mask(G2[i][j])) aE[i][j] = aE[i][j + 1] + 1;
      if (dS.mask(G2[i][j])) aS[i][j] = aS[i + 1][j] + 1;
    }
  scanf("%d", &ne);
  for (int i = 1; i <= ne; ++i) {
    static int x, y;
    static char di[5], se[5];
    scanf("%d%d%s%s", &x, &y, di, se);
    map[0][x][y].push_back(Entity(D(di[0]), se[0]));
  }
  scanf("%d%d", &nw, &lim);
  for (int i = 1; i <= nw; ++i) {
    static int typ, tim, x, y;
    scanf("%d%d%d%d", &typ, &tim, &x, &y);
    if (typ != 3)
      wep[tim].push_back(Weapon(typ, x, y));
    else
      wep[tim + 3].push_back(Weapon(3, x, y));
  }
  scanf("%d", &tm);
  while (t <= tm) {
    tick();
    ++t;
    if (cnt > lim) {
      puts("-1");
      return 0;
    }
  }
  printf("%d\n", cnt);
  return 0;
}
