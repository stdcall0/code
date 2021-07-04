#include<bits/stdc++.h>
#define Rn(a,n)a+1,a+n+1
#define Edge(T,x,y)T[x].push_back(y);T[y].push_back(x)
#define rep(i,l,r)for(int i=(l),_r_R=(r);i<=_r_R;++i)
typedef long long ll;typedef long double ld;typedef unsigned long long ull;inline ll Rl(){ll ret(0);int c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}inline int R(){int ret(0),c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}

const int N = 5e5 + 5;

std::string re;
int n, q;

std::vector<int> p;
bool b[N];
int nxt[N];

const ll P = 1e9 + 7;
ll pw[N], H[N];

inline void getPrime() {
  rep(i, 2, N) {
    if (!b[i]) {
      p.push_back(i);
      nxt[i] = i;
    }
    for (auto j : p) {
      if (1ll * i * j > N - 2) break;
      int ref = i * j;
      b[ref] = 1;
      nxt[ref] = j;
      if (!(i % ref)) break;
    }
  }
}

inline bool chk(int l, int r, int p, int q) {
#define HSH(H, l, r) (H[r] - H[l - 1] * pw[r - l + 1])
  return HSH(H, l, r) == HSH(H, p, q);
#undef HSH
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin >> n >> re;
  assert(re.size() == n);

  getPrime();
  pw[0] = 1;
  rep(i, 1, n) {
    H[i] = (H[i - 1] * 31 + re[i] - 'a') % P;
    pw[i] = pw[i - 1] * 31 % P;
  }

  std::cin >> q;
  std::vector<int> v;

  rep(_rQ, 1, q) {
    int l, r;
    std::cin >> l >> r;
    int L = r - l + 1;
    v.clear();
    while (L != 1) {
      v.push_back(nxt[L]);
      L /= nxt[L];
    }
    L = r - l + 1;
    for (auto i : v) {
      int ref = L / i;
      if (chk(l, r - ref, l + ref, r))
        L = ref;
    }

    std::cout << L << std::endl;
  }
  
  return 0;
}
