#ifndef SCENE_H_
#define SCENE_H_

#include <string>
#include <vector>
// #include "entity/model.h"

class Scene {
 public:
  Scene();

  const std::string& name();
  void set_name(const std::string& name);

  const std::vector<Model>& models();
  const std::vector<Model>& cur_models();

  void AddModel(const Model& model);
  void DeleteModel(const Model& model);

  void ClearScene();

 private:
  std::string name_;
  std::vector<Model> models_;
  std::vector<Model> cur_models_;
  std::string filename_;
};

#endif  // SCENE_H_
