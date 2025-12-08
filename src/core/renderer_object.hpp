#pragma once
#include "raylib.h"
#include "shared_state.hpp"
#include <memory>
#include <nlohmann/json.hpp>
using json = nlohmann::json;


namespace renderer {

class Object {
public:
  Object(json& obj_params);
  ~Object();

  void process(const RendererObjectTransform& new_transform);
  void display(Shared &state);
  
  RendererObjectTransform getPose();

  private:
  Model _model;
  Texture2D _texture;
  //Material _material;
  Color _tint;
  RendererObjectTransform _pose; // Right-handed, +Y == UP
  Vector3 _scale;
};


} // namespace renderer