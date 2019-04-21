#ifndef CAMERA_H_
#define CAMERA_H_

#include "point.h"
// #include "matrix.h"

class Camera {
 public:
  Camera();
  Matrix world_to_view();

 private:
  Point position_;
  Point view_direction_;
};

#endif  // CAMERA_H_
