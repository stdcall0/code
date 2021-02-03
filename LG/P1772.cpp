#include <bits/stdc++.h>
using namespace std;

int a[105][105], L[105],C[105];
struct node {
    int cnt, l, c;
    inline int& operator()() const { return l ? L[l] : C[c]; }
    inline bool operator<(const node&r) const { return cnt > r.cnt; }
} sr[105*2];

int main() {
    int n, m, az=0;
    cin >> n >> m;
    for (int i=1; i<=n; i++) {
        string s; cin >> s;
        for (int j=1; j<=m; j++) {
            a[i][j] = s[j-1] - '0'; az += a[i][j];
            L[i] += a[i][j]; C[j] += a[i][j];
        }
    }
    for (int i=1; i<=n; i++) sr[i].cnt = L[i], sr[i].l = i;
    for (int i=n+1; i<=n+m; i++) sr[i].cnt = C[i-n], sr[i].c = i-n;
    sort(sr + 1, sr + n+m+1);
    if (az == 0) {
        puts("0"); return 0;
    }
    for (int i=1; i<=n+m; ++i) {
        if (sr[i].l) {
            for (int j=1; j<=m; j++) a[sr[i].l][j] ? --az, a[sr[i].l][j] = 0 : 0;
        } else {
            for (int j=1; j<=n; j++) a[j][sr[i].c] ? --az, a[j][sr[i].c] = 0 : 0;
        }
        if (!az) {
            printf("%d\n", i);
            return 0;
        }
    }
    return 0;
}
