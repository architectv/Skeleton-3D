#ifndef CAMERA_H_
#define CAMERA_H_

#include "entity.h"
//#include "matrix.h"

class Matrix;
class Camera : Entity {
 public:
  Camera();
  Matrix world_to_view();

 private:
  Point position_;
  Point view_direction_;
};

#endif  // CAMERA_H_
