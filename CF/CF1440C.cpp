// hard ver. acceptable -> easy ver
#include <bits/stdc++.h>
using namespace std;

int a[105][105];
#define I(x) x = !x;
#define F ++o,

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    char B[105];
    int t; cin >> t; while (t--) {
        int n, m; cin >> n >> m;
        for (int i=1; i<=n; i++) {
            cin >> B;
            for (int j=1; j<=m; j++) a[i][j] = B[j-1] - '0';
        }
        ostringstream os;
        int o = 0;
        bool flg = n % 2;
        for (int i=1; i<=(n+1)/2; i++) {
            // line i * 2 - 1, i * 2
            int x=i*2-1; if (i * 2 > n) x = n-1;
            if (flg && i*2+1 == n) {
                // random fuck
                for (int j=1; j<=m/2; ++j) {
                    int y = j * 2 - 1;
                    if (a[x][y] && a[x][y+1]) {
                        F os << x << ' ' << y << ' ' << x << ' ' << (y+1) << ' ' << (x+1) <<' ' << y << endl;
                        I(a[x+1][y]);
                    } else if (a[x][y]) {
                        F os << x << ' ' << y << ' ' << (x+1) << ' ' << (y+1) << ' ' << (x+1) <<' ' << y << endl;
                        I(a[x+1][y]); I(a[x+1][y+1]);
                    } else if (a[x][y+1]) {
                        F os << (x+1) << ' ' << (y+1) << ' ' << x << ' ' << (y+1) << ' ' << (x+1) <<' ' << y << endl;
                        I(a[x+1][y]); I(a[x+1][y+1]);
                    }
                    a[x][y] = a[x][y+1] = 0;
                } 
                if (m%2 && a[x][m]) {
                    F os << (x+1) << ' ' << (m-1) << ' ' << x << ' ' << m << ' ' << (x+1) <<' ' << m << endl;
                    I(a[x+1][m]); I(a[x+1][m-1]); a[x][m] = 0;
                }
                continue;
            }
            for (int j=1; j<=m-2; j++) {
                if (a[x][j] && a[x+1][j]) {
                    F os << x << ' ' << j << ' ' << (x+1) << ' ' << j << ' ' << (x+1) << ' ' << (j+1) << endl;
                    I(a[x+1][j+1]);
                } else if (a[x][j]) {
                    F os << x << ' ' << j << ' ' << x << ' ' << (j+1) << ' ' << (x+1) << ' ' << (j+1) << endl;
                    I(a[x][j+1]); I(a[x+1][j+1]);
                } else if (a[x+1][j]) {
                    F os << (x+1) << ' ' << j << ' ' << x << ' ' << (j+1) << ' ' << (x+1) << ' ' << (j+1) << endl;
                    I(a[x][j+1]); I(a[x+1][j+1]);
                }
                a[x][j] = a[x+1][j] = 0;
            }
            int y = m-1, c = (a[x][y] + a[x+1][y] + a[x][y+1] + a[x+1][y+1]) % 2;
            if (c!=a[x][y]) F os << x << ' ' << (y+1) << ' ' << (x+1) << ' ' << y << ' ' << (x+1) << ' ' << (y+1) << endl;
            if (c!=a[x+1][y]) F os << x << ' ' << (y+1) << ' ' << x << ' ' << y << ' ' << (x+1) << ' ' << (y+1) << endl;
            if (c!=a[x][y+1]) F os << (x+1) << ' ' << y << ' ' << x << ' ' << y << ' ' << (x+1) << ' ' << (y+1) << endl;
            if (c!=a[x+1][y+1]) F os << x << ' ' << (y+1) << ' ' << x << ' ' << y << ' ' << (x+1) << ' ' << y << endl;
            a[x][y] = a[x+1][y] = a[x][y+1] = a[x+1][y+1] = 0;
        }
        cout << o << endl << os.str();
    }
    return 0;
}