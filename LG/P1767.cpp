#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long _;

struct bInt {
    vector<int> b; const int BIT;
    bInt(int BIT) : BIT(BIT), b(vector<int>()) {};
    bInt(const bInt& b) : BIT(b.BIT), b(b.b) {}
    _ operator()(int d) const {
        if (d >= b.size()) return 0;
        return b[d];
    }
    bInt operator+(const bInt& r) const {
        bInt ret(BIT);
        int t = 0;
        for (int i=0; i<max(r.b.size(), b.size()); ++i) {
            t += r(i) + operator()(i);
            ret.b.push_back(t % BIT);
            t /= BIT;
        }
        if (t) ret.b.push_back(t);
        return ret;
    }
    const bInt& operator=(const bInt& r) {
        b = r.b; return r;
    }
    bInt reversed() const {
        bInt t(*this);
        for (int i=0; i<b.size(); i++) t.b[b.size()-i-1] = b[i];
        return t;
    }
    bool paracheck() const {
        for (int i=1; i<=b.size()/2; i++)
            if (b[i-1] != b[b.size()-i]) return 0;
        return 1;
    }
};

int main() {
    _ m;  string s; cin >> m >> s; bInt n(m);
    n = 0; for (int i=s.size()-1; i>=0; --i) {
        n.b.push_back(isdigit(s[i]) ? (s[i] - '0') : (s[i] - 'A' + 10));
    }
    int step = 0;
    while (step <= 30 && !n.paracheck()) {
        n = n + n.reversed();
        ++step;
    }
    step > 30 ? puts("Impossible!") : printf("%d\n", step);
    return 0;
}