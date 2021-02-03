#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5; int n, h[N], R1[N], R2[N];
deque<int> Q; // QmIn QmAx
#define T(Q) (*--Q.end())
#define H(Q) (*Q.begin())
#define wcond(Q, x) while (!Q.empty() && (x)) 

auto r = [](){ static int F; scanf("%d", &F); return F; };

int main() {
    int a=1,n = r();
    for (int i=1; i<=n; i++) h[i] = r();
    for (int i=1; i<=n; i++) {
        // find last element >= h[i]
        wcond(Q, h[i] > h[T(Q)]) Q.pop_back();
        if (!Q.empty()) R1[i] = T(Q);
    }
    Q.clear(); for (int i=n; i>=1; i--) {
        wcond(Q, h[i] < h[T(Q)]) Q.pop_back();
        if (!Q.empty()) R1[i] = T(Q);
    }

    printf("%d\n", a);
    return 0;
}