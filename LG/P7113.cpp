#include <bits/stdc++.h>
using namespace std;

typedef __int128_t ll;
struct Frac {
	ll a, b;
	inline void Simplify() {
		ll d = __gcd(a, b);
		a /= d, b /= d;
	}
	inline void Add(const Frac& r) {
		ll fz = r.b / __gcd(r.b, b) * b;
		a = (fz / b) * a + (fz / r.b) * r.a;
		b = fz; Simplify();
	}
	inline Frac Div(ll m) { Frac r=*this; r.b*=m; return r; }
};

const int N = 1e5 + 5;
Frac a[N];
vector<int> dest[N];
bool b[N];

inline void ou128I(__int128_t x) {
  if (x == 0) return;
  ou128I(x / 10);
  putchar(x % 10 + '0');
}
inline void ou128(__int128_t x) {
  if (x < 0) putchar('-'), ou128I(-x);
  else if (x > 0) ou128I(x);
  else putchar('0');
}

int main() {
	int n, m; scanf("%d%d", &n,&m);
	for (int d,f,i=1; i<=n; ++i) {
		scanf("%d", &d);
		// if (!d) a[i].a = 1, a[i].b = 1;
		for (int j=1; j<=d; ++j) {
			scanf("%d", &f);
			dest[i].push_back(f);
			b[f] = 1;
		}
	}
	for (int i=1; i<=n; i++) if (!b[i]) a[i].a = a[i].b = 1; 
	Frac t; bool flw; do {
		flw = 0;
		for (int i=1; i<=n; i++) if (a[i].b && !dest[i].empty()) { flw = 1;
			t = a[i].Div(dest[i].size()); t.Simplify();
			for (int j=0; j<dest[i].size(); ++j) {
				if (a[dest[i][j]].b) a[dest[i][j]].Add(t);
				else a[dest[i][j]] = t;
			}
			a[i].b = 0;
		}
	} while (flw);
	for (int i=1; i<=n; i++) if (dest[i].empty()) {
    ou128(a[i].a); putchar(' '); ou128(a[i].b); putchar('\n');
	}
  cout.flush();
	return 0;
}
