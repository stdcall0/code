#include <bits/stdc++.h>
using namespace std;

char s[114514];

inline bool cmp(int ind, const char*c){
  for (int i=0; i<strlen(c); ++i)
    if (s[ind+i] != c[i]) return false;
  return true;
}

int main() {
  scanf("%s", s+1);
  int n = strlen(s+1);
  int r = n; int ans=0, v=0;
  for (int i=1; i<=n; ++i) {
    r = n-i+1; if (s[i] != '.') ++ans;
    if (r >= 3 && cmp(i, "boy")) i+=2,++v;
    else if(r>=2 && cmp(i, "bo") || r>=2 && cmp(i, "oy")) i+=1,++v;
    else if(cmp(i, "b") || cmp(i, "o")|| cmp(i, "y")) ++v;
    else if(r>=4 && cmp(i, "girl"))i+=3;
    else if(r>=3 && cmp(i, "gir")) i+=2;
    else if(r>=3 && cmp(i, "irl")) i+=2;
    else if(r>=2 && cmp(i, "gi")) i+=1;
    else if(r>=2 && cmp(i, "ir")) i+=1;
    else if(r>=2 && cmp(i, "rl")) i+=1;
  }
  printf("%d\n%d\n", v,ans-v);
  return 0;
}