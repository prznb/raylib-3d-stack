#include "renderer_object.hpp"
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

void Object::process(const RendererObjectTransform &new_pose) { _pose = new_pose; }

void Object::display(Shared &state) {
  _model.transform = MatrixRotateZYX(_pose.wf_rotation);
  DrawModel(_model, _pose.wf_translation, 1.0f, _tint);
}

RendererObjectTransform Object::getPose() { return _pose; }


} // namespace renderer