#include <bits/stdc++.h>
using namespace std;
#define Qh (Q.front())
#define Qt (*Q.rbegin())
#define int long long
const int N = 500050;
int n, d, f[N], K;
struct SJYssb {
    int x, s;
    int& operator[](int id) { return id ? s : x; }
    const int& operator[](int id)const { return id ? s : x; }
};
struct CQE {
    int T, v;
};
array<SJYssb, N> a;

bool check(int g) {
    int Lv = max(1ll, d - g), Rv = d + g;
    memset(f, ~0x7f, sizeof(f));
    int inq = 0; f[0] = 0; deque<CQE> Q;
    for (int i=1; i<=n; i++) {
        for (; inq < i && a[i].x - a[inq].x >= Lv; ++inq) {
            if (f[inq] != f[n+1]) {
                for (; !Q.empty() && Qt.v <= f[inq]; Q.pop_back());
                Q.push_back((CQE) {a[inq].x, f[inq]});
            }
        }
        for (; !Q.empty() && a[i].x - Qh.T > Rv; Q.pop_front());
        if (Q.empty()) f[i] = f[n+1]; else f[i] = Qh.v + a[i].s;
        if (f[i] >= K) return 1;
    }
    return 0;
}

signed main() {
    int L = 0, R, mid, ans=-1; cin >> n >> d >> K;
    for (int i=1; i<=n; i++) {
        scanf("%lld%lld", &a[i].x, &a[i].s);
    } R = a[n].x; R = max(R, d);
    while (L <= R) {
        mid = L + R >> 1;
        if (check(mid))
            ans = mid, R = mid - 1;
        else L = mid + 1;
    }
    printf("%lld\n", ans);
    return 0;
}