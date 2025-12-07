#include "renderer_scene.hpp"
#include "raylib.h"
#include "raymath.h"
#include "shared_state.hpp"
#include <cstdlib>


namespace renderer {

void Scene::addObject(nlohmann::json& obj_params) {
  Color c = {obj_params["color"]["r"], obj_params["color"]["g"], obj_params["color"]["b"], obj_params["color"]["a"]};
  Vector3 dim = Vector3Scale(Vector3One(), obj_params["side_length"]);

  auto new_object = std::make_unique<Object>(c, dim);
  _objects.push_back(std::move(new_object));
}

void Scene::setup(Shared &state) {}

void Scene::process(Shared &state, const std::vector<RendererObjectTransform>& updated_poses) {
  for (int i = 0; i < _objects.size(); ++i) {
    // assign updated transforms
    _objects[i]->process(updated_poses[i]);
  }
}

void Scene::display(Shared &state) {
  for (auto &object : _objects) {
    object->display(state);
  }

  if (state.debug) {
    DrawGrid(250, 2);
  }
}

} // namespace renderer