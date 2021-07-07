#include<bits/stdc++.h>
#define Rn(a,n)a+1,a+n+1
#define Edge(T,x,y)T[x].push_back(y);T[y].push_back(x)
#define rep(i,l,r)for(int i=(l),_r_R=(r);i<=_r_R;++i)
#define drep(i,l,r)for(int i=(l),_r_R=(r);i>=_r_R;--i)
typedef long long ll;typedef long double ld;typedef unsigned long long ull;inline ll Rl(){ll ret(0);int c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}inline int R(){int ret(0),c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}

const int N = 5e6 + 5;
int n;
ll c[N], ha[N], hb[N], f[N][2], x[N], p[N];

std::deque<int> Q;
auto sqr = [](auto x) { return x * x; };
inline ll X(int i) { return -c[i]; } 
inline ll Y(int i) { return f[i][1] + x[i] * hb[i] - ha[i]; }
inline ll K(int i) { return x[i]; }
inline ll B(int i) { return f[i][0] + ha[i]; }

inline ll dX(int i, int j) { return X(j) - X(i); }; inline ll dY(int i, int j) { return Y(j) - Y(i); }
#define head Q[0], Q[1]
#define tail Q[Q.size() - 2], Q[Q.size() - 1]
#define now Q[Q.size() - 1], i

int main() {
  n = R();
  drep(i, n, 1) {
    x[i] = R(), p[i] = R(), c[i] = R();
  }
  rep(i, 1, n) {
    ha[i] = ha[i - 1] + p[i] * x[i];
    hb[i] = hb[i - 1] + p[i];
  }
  Q = {1};
  f[1][0] = (1ll << 63) - 1;
  f[1][1] = c[1];
  rep(i, 2, n) {
    f[i][1] = std::min(f[i-1][0], f[i-1][1]) + c[i];

    while (Q.size() > 1 && K(i) * dX(head) >= dY(head)) Q.pop_front();
    f[i][0] = f[Q[0]][1] + x[Q[0]] * (hb[i] - hb[Q[0]]) - ha[i] + ha[Q[0]];
    // printf("Q[0]: %d; f[%d][0]: %lld\n", Q[0], i, f[i][0]);
    while (Q.size() > 1 && dY(tail) * dX(now) >= dY(now) * dX(tail)) Q.pop_back();
    Q.push_back(i);
  }
  printf("%lld\n", std::min(f[n][0], f[n][1]));
  return 0;
}

