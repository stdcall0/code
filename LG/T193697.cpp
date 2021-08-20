#include <bits/stdc++.h>
using namespace std;

char ch[105];

int main() {
  while (1) {
    scanf("%s", ch);
    if (ch[0] == '0') break;
    int m = 0;
    for (int i = ch[0] == '-' ? 1 : 0; i < strlen(ch); ++i) {
      m += ch[i] - '0';
      m %= 3;
    }
    if (m == 0 && (ch[strlen(ch) - 1] - '0') % 2 == 0) puts("1"); else puts("0");
  }
  return 0;
}
