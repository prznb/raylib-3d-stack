#include "renderer.hpp"
#include "raylib.h"
#include "raymath.h"
#include "shared_state.hpp"
#include <cstdlib>

namespace renderer {

Object::Object(SharedObjectParams& params) {
  auto p_set = params.getRender();

  if(p_set.get("TYPE") == "CUBE")
  {
    Mesh m = GenMeshCube(p_set["EDGE_LEN"],p_set["EDGE_LEN"],p_set["EDGE_LEN"]);
    _model = LoadModelFromMesh(m);
    _pose.wf_translation = {0.f, 0.f, 0.f};
    _pose.wf_rotation = {0.f, 0.f, 0.f};
    _scale = {1.0f, 1.0f, 1.0f};
    _tint = tint;
  }

}
Object::~Object() { UnloadModel(_model); };

void Object::process(RendererObjectTransform &new_pose) { _pose = new_pose; }

void Object::display(SharedState &state) {
  _model.transform = MatrixRotateZYX(_pose.wf_rotation);
  DrawModel(_model, _pose.wf_translation, 1.0f, _tint);
}

RendererObjectTransform Object::getPose() { return _pose; }

void Scene::addObject(SharedState &state) {
  int rand_idx = rand()%4;
  Color rand_color_arr[4] = {RED, BLUE, GREEN, MAROON};
  Color rand_color = rand_color_arr[rand_idx];

  auto new_object = std::make_unique<Object>(rand_color, (Vector3){5.f, 5.f, 5.f});
  _objects.push_back(std::move(new_object));
  RendererObjectTransform new_object_transform; 
  state.object_poses_renderer.push_back(new_object_transform);
}

void Scene::addGround(SharedState& state)
{
  SharedObjectParams* params = new SharedObjectParams();
  params->constructParamsCube(500, 1E3, 1E3, 1E3, DARKGREEN);
  auto new_object = std::make_unique<Object>(*params);
  _objects.push_back(std::move(new_object));
  delete params;

  RendererObjectTransform new_object_transform;
  state.object_poses_renderer.push_back(new_object_transform);
}


void Scene::setup(SharedState &state) {
  addGround(state);
  srand(time(0));
}

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