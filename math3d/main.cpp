#include "vector.h"
#include "matrix.h"
#include "transform.h"
#include <iostream>

int main() {
  Vector3 v = {1, 2};
  Vector3 g = {3, 4, 5};
  Vector3 a = v / g;
  Vector3 b(v * g);

  Vector2 c = {4, 5};
  Vector4 s = {0, 1, 2, 3};
  std::cout << Vector3::CrossProduct(a, b) << std::endl;
  std::cout << v.x() << v.y() << v.z() << std::endl;
  std::cout << c.x() << c.y() << std::endl;
  std::cout << s.x() << s.y() << s.z() << s.w() << std::endl;

  Matrix4 m(1);
  std::cout << Matrix4::identify() + m << std::endl;

  Transform t;
  std::cout << t.Scale(g).Translate(v);
}