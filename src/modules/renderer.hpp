#pragma once
#include "raylib.h"
#include "shared_state.hpp"
#include "raymath.hpp"
#include <memory>
#include <vector>


namespace renderer {


class Object {
public:
  Object();
  ~Object();

  void process(SharedState &state);

  void display(SharedState &state);
  
private:
  Model _model;
  Texture2D _texture;
  //Material _material;
  Color _tint;
  Transform _pose; // Right-handed, +Y == UP
  Vector3 _scale;
};

class Scene 
{
  std::vector<std::unique_ptr<renderer::Object>> _objects;

public:
  Scene() {};
  ~Scene() = default;

  void addObject();

  void process(SharedState& state);

  void display(SharedState &state);
};

} // namespace renderer