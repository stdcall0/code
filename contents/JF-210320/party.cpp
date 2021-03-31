#include <bits/stdc++.h>
using namespace std;

int n, m;

struct node {
  int l, r, val;
} a[400005];
int nct=1;

inline void build(int l=1, int r=n, int x=1) {
  if (l == r) return;
  int mid = l + r >> 1;
  build(l, mid, a[x].l = ++nct);
  build(mid+1, r, a[x].r = ++nct);
}

inline void invert(int L, int R, int x=1, int l=1, int r=n) {
  if (L == l && R == r) {
    
  }
}


int main() {
  scanf("%d%d", &n, &m);
  for (int opt, x, y; m--; ) {
    scanf("%d%d%d", &opt, &x, &y);
    
  }
  return 0;
}
