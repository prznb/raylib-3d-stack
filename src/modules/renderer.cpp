#include "renderer.hpp"

namespace renderer 
{

Object::Object() {
  Mesh m = GenMeshCube(40.f, 5.f, 30.f);
  _model = LoadModelFromMesh(m);
  _pose.translation = {0.f, 0.f, 0.f};
  _pose.rotation = {1.f, 0.f, 0.f, 0.f};
  _scale = {1.0f, 1.0f, 1.0f};
  _tint = RAYWHITE;
}
Object::~Object() { UnloadModel(_model); };

void Object::process(SharedState &state) { _pose = state.current_player_pose; }

void Object::display(SharedState &state) {
  Vector3 inst_orientation = QuaternionToEuler(_pose.rotation);
  _model.transform = MatrixRotateXYZ(inst_orientation);
  DrawModel(_model, _pose.translation, 1.0f, WHITE);
}

void Scene::addObject() {
  auto new_object = std::make_unique<Object>();
  _objects.push_back(std::move(new_object));
}

void Scene::process(SharedState &state) {
  for (auto &object : _objects) {
    object->process(state);
  }
}

void Scene::display(SharedState &state) {
  for (auto &object : _objects) {
    object->display(state);
  }
}


} // namespace renderer