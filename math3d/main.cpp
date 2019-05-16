#include <iostream>
#include "vector.h"

int main() {
  Vector3 a = {1, 2, 3}, b = {-1, -1, -2};
  std::cout << Vector3::CrossProduct(a, b) << std::endl;
  return 0;
}
