#include <cstdio>
#include "color.hpp"
#include "util.hpp"

/*
|----|    0 1 2 
|    |    3   4
|----|    5 6 7
|    |    8   9
|----|    10 11 12
*/


int main() {
  while (1) {
    printf("%s ", ~CC[rand()]);
  }
  return 0;
}
