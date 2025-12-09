#include "renderer_object.hpp"
#include "raylib.h"
#include "raymath.h"
#include "shared_state.hpp"
#include <cstdlib>


namespace renderer {

Object::Object(json& obj_params) 
{
  if(obj_params["type"] == "cube")
  {
    Mesh m = GenMeshCube(obj_params["dimensions"]["width"],obj_params["dimensions"]["height"],obj_params["dimensions"]["length"] );
    _model = LoadModelFromMesh(m);
  }
  else if(obj_params["type"] == "sphere")
  {
    float radius = obj_params["dimensions"]["radius"];
    int rings = obj_params["resolution"];
    int slices = obj_params["resolution"];
    Mesh m = GenMeshSphere(radius, rings, slices);
    _model = LoadModelFromMesh(m);
  }
  else if(obj_params["type"] == "cylinder") 
  {
    Mesh m = GenMeshCylinder(obj_params["dimensions"]["radius"], obj_params["dimensions"]["height"], obj_params["resolution"]);
    _model = LoadModelFromMesh(m);
  }


  Color tint = {obj_params["color"]["r"], obj_params["color"]["g"], obj_params["color"]["b"], obj_params["color"]["a"]};
  
  // no needed to initialize - will get updated from physics
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