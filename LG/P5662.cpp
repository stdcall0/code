#include <bits/stdc++.h>
using namespace std;

const int N = 105, M = 100005;
int n, m, cm, P[N][N], F[M];

int main() {
    cin >> n >> m >> cm;
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) {
            scanf("%d", &P[i][j]);
        }
    }
    for (int D=1; D<n; D++) {
        memset(F, ~0x3f, sizeof(F)); F[cm] = cm;
        for (int i=1; i<=m; i++) {
            for (int j=cm; j>=P[D][i]; --j)
                F[j-P[D][i]] = max(F[j] + P[D+1][i] - P[D][i], F[j-P[D][i]]);
        }
        cm = *max_element(F, F+cm+1);
    }
    printf("%d\n", cm);
    return 0;
}
