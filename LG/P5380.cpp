#include <bits/stdc++.h>
using namespace std;

struct Solver {
  enum Type { None, Captain, Guard, Elephant, Horse, Car, Duck, Soldier };
  const string CType[8] = {"", "captain", "guard", "elephant", "horse", "car", "duck", "soldier"};
  enum Color { Red, Blue } player;
  const string CColor[2] = {"red", "blue"};
  struct Node { Type t; Color c; } B[10][9];
  typedef pair<int, int> Location;
  typedef vector<Location> LocArray;
  Location capR, capB; bool ended = 0;
  const LocArray CDelta[8] = { {}, {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}, {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}}, {{-2, -2}, {-2, 2}, {2, -2}, {2, 2}}, {{-1, -2}, {-2, -1}, {-1, 2}, {2, -1}, {1, -2}, {-2, 1}, {1, 2}, {2, 1}}, {}, {{-2, -3}, {-3, -2}, {-2, 3}, {3, -2}, {2, -3}, {-3, 2}, {2, 3}, {3, 2}}, {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}} };
  const LocArray CPolicy[8] = { {}, {}, {}, CDelta[2], {{0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, 0}, {0, 1}, {1, 0}}, {{-1, -2}, {-2, -1}, {-1, 2}, {2, -1}, {1, -2}, {-2, 1}, {1, 2}, {2, 1}}, {{0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, 0}, {0, 1}, {1, 0}}, {} };
  Solver() : capR({0, 4}), capB(9, 4), player(Red) {
    B[3][0] = B[3][2] = B[3][4] = B[3][6] = B[3][8] = {Soldier, Red};
    B[6][0] = B[6][2] = B[6][4] = B[6][6] = B[6][8] = {Soldier, Blue};
    B[0][0] = B[0][8] = {Car, Red}; B[9][0] = B[9][8] = {Car, Blue};
    B[0][1] = B[0][7] = {Horse, Red}; B[9][1] = B[9][7] = {Horse, Blue};
    B[2][0] = B[2][8] = {Duck, Red}; B[7][0] = B[7][8] = {Duck, Blue};
    B[0][2] = B[0][6] = {Elephant, Red}; B[9][2] = B[9][6] = {Elephant, Blue};
    B[0][3] = B[0][5] = {Guard, Red}; B[9][3] = B[9][5] = {Guard, Blue};
    B[0][4] = {Captain, Red}; B[9][4] = {Captain, Blue};
  }
  inline bool withinBoard(int x, int y) { return clamp(x, 0, 9) == x && clamp(y, 0, 8) == y; }
  inline bool checkPolicy(const Location& policy, int x, int y) {
    int p = x + policy.first, q = y + policy.second;
    return withinBoard(p, q) && B[p][q].t == None;
  }
  inline bool inArray(const Location& loc, const LocArray& array) { for (const auto& x : array) if (x == loc) return 1; return 0; }
  inline string node2str(const Node& node) { if (node.t == None) return "NA"; return CColor[node.c] + " " + CType[node.t]; }
  inline LocArray extend(int x, int y) {
    auto& b = B[x][y];
    if (b.t == None) return LocArray();
    LocArray res({});
    if (b.t == Car) {
      for (int i = x - 1; i >= 0; --i) { if (B[i][y].t != None && B[i][y].c != b.c || B[i][y].t == None) res.push_back({i, y}); if (B[i][y].t != None) break; }
      for (int i = x + 1; i < 10; ++i) { if (B[i][y].t != None && B[i][y].c != b.c || B[i][y].t == None) res.push_back({i, y}); if (B[i][y].t != None) break; }
      for (int i = y - 1; i >= 0; --i) { if (B[x][i].t != None && B[x][i].c != b.c || B[x][i].t == None) res.push_back({x, i}); if (B[x][i].t != None) break; }
      for (int i = y + 1; i < 9; ++i) { if (B[x][i].t != None && B[x][i].c != b.c || B[x][i].t == None) res.push_back({x, i}); if (B[x][i].t != None) break; }
    } else {
      for (int i = 0; i < CDelta[b.t].size(); ++i) {
        int p = x + CDelta[b.t][i].first, q = y + CDelta[b.t][i].second;
        if (!withinBoard(p, q)) continue;
        if (B[p][q].t != None && B[p][q].c == b.c) continue;
        if (!CPolicy[b.t].empty()) {
          if (!checkPolicy(CPolicy[b.t][i], x, y)) continue;
          if (b.t == Duck && !checkPolicy(CPolicy[Car][i], x, y)) continue;
        }
        res.push_back({p, q});
      }
    }
    return res;
  }
  inline string gmSta() { // ret: 0 = normal 1 = checkmate 2 = ended
    if (ended) return "no;yes";
    for (int i = 0; i < 10; ++i) for (int j = 0; j < 9; ++j)
      if (B[i][j].t != None) {
        LocArray v(extend(i, j));
        if (inArray(capR, v) || inArray(capB, v))
          return "yes;no";
      }
    return "no;no";
  }
  inline void invalid() { puts("Invalid command"); }
  inline void DoMove(int x, int y, int p, int q) {
    if (ended || B[x][y].t == None || B[x][y].c != player) return invalid();
    LocArray v(extend(x, y));
    if (!inArray({p, q}, v)) return invalid();
    string src = node2str(B[x][y]), dest = node2str(B[p][q]);
    if (B[p][q].t == Captain) ended = 1;
    B[p][q] = B[x][y]; B[x][y].t = None;
    if (B[p][q].t == Captain) if (B[p][q].c == Red) capR = {p, q}; else capB = {p, q};
    printf("%s;%s;%s\n", src.c_str(), dest.c_str(), gmSta().c_str());
    player = (Color)(1 - player);
  }
} _;

int main() {
  int T, x, y, p, q; scanf("%d", &T); while (T--) {
    scanf("%d%d%d%d", &x, &y, &p, &q);
    _.DoMove(x, y, p, q);
  }
  return 0;
}
