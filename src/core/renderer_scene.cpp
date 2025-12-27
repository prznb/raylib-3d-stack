#include "renderer_scene.hpp"
#include "raylib.h"
#include "raymath.h"
#include "shared_state.hpp"
#include "types.hpp"
#include <cstdlib>


namespace renderer {

void Scene::addObject(nlohmann::json& obj_params) {
  auto new_object = _generator.create(obj_params);
  _objects.push_back(std::move(new_object));
}

void Scene::setup(Shared &state) {}

void Scene::process(Shared &state, RendererObjectRepresentations& updated_poses) 
{
  for (int i = 0; i < _objects.size(); ++i) {
    _objects[i]->process(i, updated_poses);
  }

  state.selected_object_pose = _objects[state.selected_vehicle_body_idx]->getPose();
}

void Scene::display(Shared &state) {
  for (auto &object : _objects) {
    object->display(state);
  }

  if (state.debug) {
    DrawGrid(250, 1);
  }
}

} // namespace renderer