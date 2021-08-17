#include <bits/stdc++.h>
using namespace std;

multiset<int> S;

int main() {
  S.insert(-0x7fffffff); S.insert(0x7fffffff);
  int Q; scanf("%d", &Q);
  while (Q--) {
    static int op, x;
    scanf("%d%d", &op,&x);
    multiset<int>::iterator it, i; int idx = 0;
    switch(op) {
        case 1:
          it = S.lower_bound(x); i = S.begin();
          while (i != it) ++idx, ++i;
          printf("%d\n", idx);
          break;
        case 2:
          it = S.begin();
          while (x--) ++it;
          printf("%d\n", *it);
          break;
        case 3:
          it = S.lower_bound(x);
          printf("%d\n", *--it);
          break;
        case 4:
          it = S.upper_bound(x);
          printf("%d\n", *it);
          break;
        case 5:
          S.insert(x);
    }
  }
  return 0;
}
