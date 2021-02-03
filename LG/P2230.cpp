#include <bits/stdc++.h>
using namespace std;
int n, k;
int f[1005][1005], a[1005];
int dfs(int x, int y) {
    if (1 == x) return a[y];
    if (f[x][y]) return f[x][y];
    if (y == k) return f[x][y] = dfs(x,1) + x*x*a[y];
    f[x][y] = dfs(x-1, y+1) + a[y];
    for (int i=2; i<x; i++) f[x][y] = min(f[x][y], dfs(x-i, y+1) + i*i*a[y] + dfs(i, 1));
    return f[x][y];
}
int main () {
    cin >> n >> k;
    for (int i=1; i<=k; i++) scanf("%d", &a[i]);
    sort(a+1, a+1+k); printf("%d\n", dfs(n,1));
    return 0;
}
