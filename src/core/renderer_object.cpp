#include "renderer_object.hpp"
#include "raylib.h"
#include "raymath.h"
#include "shared_state.hpp"
#include "types.hpp"
#include <cstdlib>
#include <memory>

namespace renderer {

// Object
Object::Object(json &obj_params) {
  if (obj_params["type"] == "cube") {
    Mesh m = GenMeshCube(obj_params["dimensions"]["width"],
                         obj_params["dimensions"]["height"],
                         obj_params["dimensions"]["length"]);
    _model = LoadModelFromMesh(m);
  } else if (obj_params["type"] == "sphere") {
    float radius = obj_params["dimensions"]["radius"];
    int rings = obj_params["resolution"];
    int slices = obj_params["resolution"];
    Mesh m = GenMeshSphere(radius, rings, slices);
    _model = LoadModelFromMesh(m);
  } else if (obj_params["type"] == "cylinder") {
    Mesh m = GenMeshCylinder(obj_params["dimensions"]["radius"],
                             obj_params["dimensions"]["height"],
                             obj_params["resolution"]);
    _model = LoadModelFromMesh(m);
  }

  Color tint = {obj_params["color"]["r"], obj_params["color"]["g"],
                obj_params["color"]["b"], obj_params["color"]["a"]};

  // no needed to initialize - will get updated from physics
  _pose.wf_translation = {0.f, 0.f, 0.f};
  _pose.wf_rotation = {0.f, 0.f, 0.f};
  _scale = {1.0f, 1.0f, 1.0f};
  _tint = tint;
}
Object::~Object() { UnloadModel(_model); };

void Object::process(int scene_index, RendererObjectRepresentations &rot) {
  _pose = rot.base_transforms[scene_index];
  // Do not evaluate subtransforms for primitives
}

void Object::display(Shared &state) {
  _model.transform = MatrixRotateZYX(_pose.wf_rotation);
  DrawModel(_model, _pose.wf_translation, 1.0f, _tint);
}

// Vehicle::Object
Vehicle::Vehicle(json &obj_params) : Object(obj_params) {
  if (obj_params["model"] == "debug_m3") 
  {
    Model allModelMeshes = LoadModel("assets/models/_extras/m3.glb");
    Mesh chassis = allModelMeshes.meshes[0];
    _model = LoadModelFromMesh(chassis); // assign base model

    for(int i = 1; i<allModelMeshes.meshCount; ++i)
    {
      Model tmp_submodel = LoadModelFromMesh(allModelMeshes.meshes[i]);
      _submodels.push_back(std::move(tmp_submodel));
    }


    _model_rotation_offset = {-PI/2.f, 0.f, 0.f};
    _model_translation_offset = {0.f ,-0.45f*(float)obj_params["dimensions"]["chassis"]["height"], -0.1f};
    //_model_translation_offset = Vector3Zero();
  } 
  else {
    Mesh m = GenMeshCube(obj_params["dimensions"]["chassis"]["width"],
                         obj_params["dimensions"]["chassis"]["height"],
                         obj_params["dimensions"]["chassis"]["length"]);
    _model = LoadModelFromMesh(m);
  }

  _wheel_radius = obj_params["dimensions"]["wheels"]["radius"];
  _tint = GREEN;
}

void Vehicle::process(int scene_index, RendererObjectRepresentations &rot) {
  Object::process(scene_index, rot);
  _wheel_transforms = rot.subtransforms[scene_index];
}

void Vehicle::display(Shared &state) 
{
  Matrix tmp_physics_rot = MatrixRotateXYZ(_pose.wf_rotation);
  Vector3 rotated_offset = Vector3Transform(_model_translation_offset, tmp_physics_rot);

  // base model
  _pose.wf_rotation = Vector3Add(_pose.wf_rotation, _model_rotation_offset);
  _model.transform = MatrixRotateZYX(_pose.wf_rotation);
  DrawModelWires(_model, Vector3Add(_pose.wf_translation,rotated_offset), 1.0f, BLACK);
  DrawModel(_model, Vector3Add(_pose.wf_translation,rotated_offset), 1.0f, RAYWHITE);
  
  // chassis extras
  for(int i = 0; i<7; ++i)
  {
    _submodels[i].transform = MatrixRotateZYX(_pose.wf_rotation);
    DrawModelWires(_submodels[i],Vector3Add(_pose.wf_translation,rotated_offset), 1.0f, RED);
  }

  // Wheels
  int model_idx; 
  int transform_idx = 0;
  bool flip = true;
  for(model_idx = 8; model_idx<16; model_idx += 2)
  {
    Vector3 rot_zyx = _wheel_transforms[transform_idx].wf_rotation;
    rot_zyx.x = -rot_zyx.x;
    if(flip)
    {
      rot_zyx = Vector3Add(rot_zyx,{0.f, PI, 0.f});
    }

    // Tire
    _submodels[model_idx].transform = MatrixRotateZYX(rot_zyx);
    DrawModelWires(_submodels[model_idx], _wheel_transforms[transform_idx].wf_translation, 1.0f, BLUE);

    // Rim
    _submodels[model_idx+1].transform = MatrixRotateZYX(rot_zyx);
    DrawModelWires(_submodels[model_idx+1], _wheel_transforms[transform_idx].wf_translation, 1.0f, DARKBLUE);

    transform_idx++;
    flip = !flip;
  }


}

// Transform
RendererObjectTransform Object::getPose() { return _pose; }

// Factory
std::unique_ptr<Object> ObjectFactory::create(json &recipe) {
  if (recipe["type"] == "car") {
    return std::make_unique<Vehicle>(recipe);
  }
  return std::make_unique<Object>(recipe);
}

} // namespace renderer