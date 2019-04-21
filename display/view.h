#ifndef VIEW_H_
#define VIEW_H_

#include "scene.h"
// #include "entity/camera.h"
// #include "entity/surface.h"

class View {
 public:
  View();
  
  DrawScene(const Scene& scene);

  Camera& camera();

 private:
  Camera camera_;

  void DrawModel(const Model& model);
  void DrawSurface(const Surface& surface);
};

#endif  // VIEW_H_
