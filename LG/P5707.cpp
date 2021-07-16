#include <cstdio>

int main() {
  int s, v;
  scanf("%d%d", &s,&v);
  int mi = s / v + (bool)(s % v) + 10;
  int H = (7 - mi / 60 + 24) % 24, M = 60 - mi % 60;
  printf("%.2d:%.2d\n", H,M);
  return 0;
}
