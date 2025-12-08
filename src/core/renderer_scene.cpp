#include "renderer_scene.hpp"
#include "raylib.h"
#include "raymath.h"
#include "shared_state.hpp"
#include <cstdlib>


namespace renderer {

void Scene::addObject(nlohmann::json& obj_params) {
  auto new_object = std::make_unique<Object>(obj_params);
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