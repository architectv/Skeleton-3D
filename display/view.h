#ifndef VIEW_H_
#define VIEW_H_

#include "scene.h"
#include "camera.h"
#include "surface.h"

class View {
 public:

  void DrawScene();
  void DrawModel(const Model& model);
  void DrawSurface(const Surface& surface);

 private:
  Scene scene_;
  Camera camera_;
};

#endif  // VIEW_H_
