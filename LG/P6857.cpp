#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ll T,n; scanf("%lld",&T); while(T--) {
        scanf("%lld", &n);
        if (n & 1) printf("%lld\n", n*(n-1)/2);
        else printf("%lld\n", n*(n-1)/2 - (n-2)/2);
    }
    return 0;
}