#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<ll> a; ll n, t, T, t2;

struct BITd {
    ll tree[200005 * 8];
    inline void add(int x, int v=1) {
        for (++x, ++x; x <= 400002; x += x & (-x)) tree[x] += v;
    }
    inline ll query(int x) {
        ll r=0; for(++x, ++x; x; x -= x & (-x)) r+=tree[x];
        return r;
    }
} BIT;

typedef vector<pair<ll, int> > _;
_ uni;
ll rem[200005], remt[200005];

int main () {
    cin >> n >> T;
    for (int i=1; i<=n; i++) scanf("%lld", &t), t2 += t, a.push_back(t2);
    for (int i=0; i<n; i++) {
        uni.push_back(make_pair(a[i], i));
        uni.push_back(make_pair(a[i]-T, i+n));
    }
    uni.push_back(make_pair(0, -1));
    sort(uni.begin(), uni.end());
    ll lv=uni.begin()->first, id=1, zid=-1;
    if (uni.begin()->second >= n) remt[uni.begin()->second-n] = id;
    else if (uni.begin()->second == -1) zid=1; else rem[uni.begin()->second] = id;
    for (_::iterator it = uni.begin() + 1; it != uni.end(); ++it) {
        if (lv != it->first) {
            lv = it->first; ++id;
        }
        if (it->second >= n) remt[it->second - n] = id;
        else if (it->second==-1) zid=id; else rem[it->second] = id;
    }
    // sum[r] - t < sum[l-1];
    ll ans=0, cs=1;
    BIT.add(zid, 1);
    for (int i=0; i<n; i++) {
        ans += cs - BIT.query(remt[i]);
        BIT.add(rem[i], 1); ++cs;
    }
    cout << ans << endl;
    return 0;
}
