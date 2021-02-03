#include <bits/stdc++.h>
using namespace std;

unsigned x; char buffer[10];

int main() {
    assert(scanf("#%X", &x) == 1);
    x = ~x; x &= (1 << 24) - 1;
    sprintf(buffer, "%X", x);
    putchar('#');
    for (int d=6-strlen(buffer); d; d--)
        putchar('0');
    printf("%s\n", buffer);
    return 0;
}
