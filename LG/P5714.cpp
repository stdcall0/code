#include <iostream>

int main() {
  double m,h;
  std::cin>>m>>h;
  double nmsl = m / h / h;
  if (nmsl < 18.5) puts("Underweight");
  else if (nmsl < 24) puts("Normal");
  else {
    std::cout << nmsl << std::endl;
    puts("Overweight");
  }
  return 0;
}
