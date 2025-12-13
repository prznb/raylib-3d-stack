#pragma once
#include "raylib.h"
#include "shared_state.hpp"
#include <memory>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace renderer {

class Object {
public:
  Object(json &obj_params);
  ~Object();

  virtual void process(int scene_index, RendererObjectRepresentations& rot);
  virtual void display(Shared &state);

  RendererObjectTransform getPose();

protected:
  Model _model;
  Texture2D _texture;
  // Material _material;
  Color _tint;
  RendererObjectTransform _pose; // Right-handed, +Y == UP
  Vector3 _scale;
};

class Vehicle : public Object 
{

std::vector<RendererObjectTransform> _wheel_transforms;
std::vector<Model> _submodels;

float _wheel_radius;
Vector3 _model_rotation_offset = {0, 0, 0}; 
Vector3 _model_translation_offset = {0, 0, 0};

public:
  Vehicle(json &obj_params);
  ~Vehicle() = default;

  void process(int scene_index, RendererObjectRepresentations& rot) override;
  void display(Shared &state) override;
};

class ObjectFactory {
public:
  ObjectFactory() {};
  ~ObjectFactory() = default;

  std::unique_ptr<Object> create(json &recipe);
};

} // namespace renderer