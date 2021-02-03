/// @tags: luogu; template; dp; 单调队列; 滑动窗口
#include <bits/stdc++.h>
using namespace std;

int n, k, a[(int)1e6 + 5];
deque<int> Qi, Qx;
ostringstream s1, s2;

int main() {
    scanf("%d%d", &n,&k);
    for (int i=1; i<=n; i++) {
        scanf("%d", &a[i]);
        while (!Qi.empty() && i-*Qi.begin()>=k) Qi.pop_front();
        while (!Qx.empty() && i-*Qx.begin()>=k) Qx.pop_front();
        while (!Qi.empty() && a[i] <= a[*--Qi.end()]) Qi.pop_back();
        while (!Qx.empty() && a[i] >= a[*--Qx.end()]) Qx.pop_back();
        Qi.push_back(i); Qx.push_back(i);
        if (i >= k) s1 << a[*Qi.begin()] << ' ',
            s2 << a[*Qx.begin()] << ' ';
    }
    printf("%s\n%s\n", s1.str().c_str(), s2.str().c_str());
    return 0;
}