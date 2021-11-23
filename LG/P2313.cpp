#include <cstdio>
#include <algorithm>

int R = 0, C = 0;
double rx1[505], rx2[505], ry1[505], ry2[505];
double cx[505], cy[505], cr[505];

inline int count(double x, double y) {
  int ret = 0;
  for (int i = 1; i <= R; ++i)
    if (x > rx1[i] && x < rx2[i] && y > ry1[i] && y < ry2[i])
      ++ret;
  for (int i = 1; i <= C; ++i)
    if ((x - cx[i]) * (x - cx[i]) + (y - cy[i]) * (y - cy[i]) < cr[i] * cr[i])
      ++ret;
  return ret;
}

int main() {
  int n, m;
  scanf("%d%d", &n,&m);
  for (int i = 1; i <= n; ++i) {
    static char op[5]; double x,y,p,q;
    scanf("%s%lf%lf%lf", op,&x,&y,&p);
    if (op[0] == 'c') {
      ++C;
      cx[C] = x, cy[C] = y, cr[C] = p;
    } else {
      scanf("%lf", &q);
      ++R;
      rx1[R] = std::min(x, p);
      rx2[R] = std::max(x, p);
      ry1[R] = std::min(y, q);
      ry2[R] = std::max(y, q);
    }
  }
  for (int i = 1; i <= m; ++i) {
    static double x, y;
    scanf("%lf%lf", &x, &y);
    printf("%d\n", count(x, y));
  }
  return 0;
}
