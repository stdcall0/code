#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 505, M_sz = 5, MOD = 998244353; int m, n;
string s; struct mat; void print_mat(const mat&);

struct mat
{
    const int &sz;
    ll a[M_sz][M_sz];
    mat() : sz(m) { memset(a, 0, sizeof a); }
    mat(const mat &r) : sz(m)
    {
        for (int i=0; i<sz; i++) for (int j=0; j<sz; j++) a[i][j] = r.a[i][j];
    }
    inline const mat& operator=(const mat &r)
    {
        for (int i=0; i<sz; i++) for (int j=0; j<sz; j++) a[i][j] = r.a[i][j];
        return r;
    }
    inline mat operator-(const mat &T) const
    {
        mat res;
        for (int i = 0; i < sz; ++i)
            for (int j = 0; j < sz; ++j)
            {
                res.a[i][j] = (a[i][j] - T.a[i][j]) % MOD;
            }
        return res;
    }
    inline mat operator+(const mat &T) const
    {
        mat res;
        for (int i = 0; i < sz; ++i)
            for (int j = 0; j < sz; ++j)
            {
                res.a[i][j] = (a[i][j] + T.a[i][j]) % MOD;
            }
        return res;
    }
    inline mat operator*(const mat &T) const
    {
        mat res;
        int r;
        for (int i = 0; i < sz; ++i)
            for (int k = 0; k < sz; ++k)
            {
                r = a[i][k];
                for (int j = 0; j < sz; ++j)
                    res.a[i][j] += T.a[k][j] * r, res.a[i][j] %= MOD;
            }
        return res;
    }
    inline mat operator^(ll x) const
    {
        mat res, bas;
        for (int i = 0; i < sz; ++i)
            res.a[i][i] = 1;
        for (int i = 0; i < sz; ++i)
            for (int j = 0; j < sz; ++j)
                bas.a[i][j] = a[i][j] % MOD;
        while (x)
        {
            if (x & 1)
                res = res * bas;
            bas = bas * bas;
            x >>= 1;
        }
        return res;
    }
};
void print_mat(const mat&r) {
    printf("Mat at %u: [%dx%d]\n", &r, r.sz, r.sz);
    for (int i=0; i<m; ++i) {
        for (int j=0; j<m; ++j) printf("%lld ", r.a[i][j]);
        puts("");
    }
}
mat A, D[N][N], F[N], pw[N];

int main()
{
    cin >> s >> m;
    n = s.size();
    for (int i = 0; i < m; i++)
        A.a[i][m-1] = 1;
    for (int i = 1; i < m; i++)
        A.a[i][i - 1] = 1;
    for (int i=0; i<=9; i++) pw[i] = A^i;
    // printf("A "); print_mat(A);
    for (int i = 1; i <= n; i++)
    {
        D[i][i] = pw[s[i-1] - '0'];
        // printf("D[%d][%d] ", i,i); print_mat(D[i][i]);
        for (int j = i + 1; j <= n; j++)
        {
            D[i][j] = (D[i][j - 1] ^ 10) * pw[s[j-1] - '0'];
            // printf("D[%d][%d] ", i,j); print_mat(D[i][j]);
        }
    }
    for (int i=0; i<m; i++) F[0].a[i][i] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= i - 1; ++j)
        {
            F[i] = F[i] + (D[j + 1][i] * F[j]);
        }
    }
    ll ans = 0;
    
    for (int j = 0; j < m; j++)
        (ans += F[n].a[0][j]) %= MOD;
    printf("%lld\n", ans);
    return 0;
}