/// @tags: template
#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("Ofast","-funroll-loops","-fdelete-null-pointer-checks")
#pragma GCC target("ssse3","sse3","sse2","sse","avx2","avx")

typedef long long ll;
template<typename T>
void read(T& r) {
    T ret(0); char c; bool neg;
    while (!isdigit(c = getchar())) neg = c == '-';
    ret = c - '0'; while (isdigit(c = getchar())) ret *= 10, ret += c - '0';
}

int main() {
    return 0;
}