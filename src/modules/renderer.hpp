#pragma once
#include "raylib.h"
#include "shared_state.hpp"
#include <memory>


namespace renderer {


class Object {
public:
  Object(SharedObjectParams& params);
  ~Object();

  void process(RendererObjectTransform& new_transform);
  void display(SharedState &state);
  
  RendererObjectTransform getPose();

  private:
  Model _model;
  Texture2D _texture;
  //Material _material;
  Color _tint;
  RendererObjectTransform _pose; // Right-handed, +Y == UP
  Vector3 _scale;
};

class Scene 
{
  std::vector<std::unique_ptr<renderer::Object>> _objects;

public:
  Scene() {};
  ~Scene() = default;

  void addObject(SharedState& state);

  void addGround(SharedState& state);

  void setup(SharedState& state);

  void process(SharedState& state);

  void display(SharedState& state);
};

} // namespace renderer