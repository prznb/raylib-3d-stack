#include "renderer.hpp"
#include "raylib.h"
#include "raymath.h"
#include "shared_state.hpp"
#include <cstdlib>


namespace renderer {

Object::Object(Color tint, Vector3 mesh_dimensions) {
  Mesh m = GenMeshCube(mesh_dimensions.x, mesh_dimensions.y, mesh_dimensions.z);
  _model = LoadModelFromMesh(m);
  _pose.wf_translation = {0.f, 0.f, 0.f};
  _pose.wf_rotation = {0.f, 0.f, 0.f};
  _scale = {1.0f, 1.0f, 1.0f};
  _tint = tint;
}
Object::~Object() { UnloadModel(_model); };

void Object::process(RendererObjectTransform &new_pose) { _pose = new_pose; }

void Object::display(SharedState &state) {
  _model.transform = MatrixRotateZYX(_pose.wf_rotation);
  DrawModel(_model, _pose.wf_translation, 1.0f, _tint);
}

RendererObjectTransform Object::getPose() { return _pose; }

void Scene::addObject(nlohmann::json& obj_params) {
  Color c = {obj_params["color"]["r"], obj_params["color"]["g"], obj_params["color"]["b"], obj_params["color"]["a"]};
  Vector3 dim = Vector3Scale(Vector3One(), obj_params["side_length"]);

  auto new_object = std::make_unique<Object>(c, dim);
  _objects.push_back(std::move(new_object));
}

void Scene::setup(SharedState &state) {}

void Scene::process(SharedState &state) {
  for (int i = 0; i < _objects.size(); ++i) {
    // assign updated transforms
    _objects[i]->process(state.object_poses_renderer[i]);
  }
}

void Scene::display(SharedState &state) {
  for (auto &object : _objects) {
    object->display(state);
  }

  if (state.debug) {
    DrawGrid(250, 2);
  }
}

} // namespace renderer