#include <bits/stdc++.h>

#define Rn(a, n) a + 1, a + n + 1
#define Edge(T, x, y) T[x].push_back(y); T[y].push_back(x) //; printf("Edge #%s: %d - %d\n", #T, x, y)
typedef long long ll;
typedef unsigned long long ull;
inline ll R() {
  ll ret(0), c(0); bool neg(0); while (!isdigit(c = std::getchar())) neg = c == '-';
  ret = c - '0'; while (isdigit(c = std::getchar())) ret *= 10ll, ret += c - '0';
  return neg ? -ret : ret;
}

const int N = 1e5 + 5;

int main() {
  
  return 0;
}
