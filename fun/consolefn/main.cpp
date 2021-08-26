// LCD Example
// Run on unix shell
#include <cstdio>
#include "color.hpp"
#include "util.hpp"

/*
|----|    0 1 2 
|    |    3   4
|----|    5 6 7
|    |    8   9
|----|    10 11 12

011112
0    2
?3333?
4    6
455556
*/
const int NumArray[10] = {
  ((1 << 7) - 1) ^ (1 << 3),
  (1 << 2) | (1 << 6),
  (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5),
  (1 << 1) | (1 << 2) | (1 << 3) | (1 << 6) | (1 << 5)
};

void PrintToCharArray(char (*mat)[6], int sta) {
  sta &= (1 << 7) - 1;
  for (int i = 0; i < 5; ++i) for (int j = 0; j < 5; ++j) mat[i][j] = ' ';
  if (!sta) return;
  if (sta & 1 || sta & 8 || sta & 16) mat[2][0] = '|';
  if (sta & 4 || sta & 8 || sta & (1 << 6)) mat[2][5] = '|';
  if (sta & 1) {
    mat[0][0] = mat[1][0] = '|';
  }
  if (sta & 4) {
    mat[0][4] = mat[1][4] = '|';
  }
  if (sta & 16) {
    mat[3][0] = mat[4][0] = '|';
  }
  if (sta & (1 << 6)) {
    mat[3][4] = mat[4][4] = '|';
  }
  if (sta & 2) {
    mat[0][1] = mat[0][2] = mat[0][3] = mat[0][4] = '-';
  }
  if (sta & 8) {
    mat[2][1] = mat[2][2] = mat[2][3] = mat[2][4] = '-';
  }
  if (sta & (1 << 5)) {
    mat[4][1] = mat[4][2] = mat[4][3] = mat[4][4] = '-';
  }
}


int main() {
  const int N = 6, M = 6;
  char buffer[N][M];
  while (1) {
    PrintToCharArray(buffer, NumArray[rand() % 4]);
    for (int i = 0; i < 6; ++i) {
      // printf("%s", ~CC[rand()]);
      for (int j = 0; j < 6; ++j) {
        printf("%c", buffer[i][j]);
      }
      puts("");
      //printf("%s\n", ~CC[M::Reset]);
    }
    puts("");
  }
  return 0;
}
