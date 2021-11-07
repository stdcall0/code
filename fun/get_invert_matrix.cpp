#include <bits/stdc++.h>
using namespace std;

// 输入 n 和 矩阵，计算逆矩阵。

const int N = 1145;
int n, a[N][N];

int main() {
  scanf("%d", &n);
  for (int i=1; i<=n; ++i) for (int j=1; j<=n; ++j)
    scanf("%d", &a[i]);
  
  return 0;
}