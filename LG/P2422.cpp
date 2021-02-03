#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 100555;
int n; ll a[N], s[N], ans=0; int cm[N], st[N], tp = 0;

inline void gAns(int x, int r) {
    int l = cm[x];
    ans = max(ans, a[x] * (s[r] - s[l-1]));
}

int main() {
    scanf("%d", &n);
    for (int i=1; i<=n; i++) scanf("%lld", &a[i]), s[i] = s[i-1] + a[i];
    st[0]=0; st[tp = 1] = 1; cm[1] = 1;
    for (int i=2; i<=n; i++) {
        while (a[i] <= a[st[tp]]) --tp;
        cm[i] = st[tp] + 1; st[++tp] = i;
    }
    st[0]=n+1; st[tp = 1] = n; gAns(n, n);
    for (int i=n-1; i>=1; i--) {
        while (a[i] <= a[st[tp]]) --tp;
        gAns(i, st[tp] - 1); st[++tp] = i;
    }
    printf("%lld\n", ans);
    return 0;
}
