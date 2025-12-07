#pragma once
#include "raylib.h"
#include "shared_state.hpp"
#include <memory>
#include <nlohmann/json.hpp>
#include "renderer_object.hpp"

using json = nlohmann::json;

namespace renderer {


class Scene 
{
  std::vector<std::unique_ptr<renderer::Object>> _objects;

public:
  Scene() {};
  ~Scene() = default;

  void addObject(json& obj_params);

  void setup(Shared& state);

  void process(Shared &state, const std::vector<RendererObjectTransform>& updated_poses);

  void display(Shared& state);
};

} // namespace renderer