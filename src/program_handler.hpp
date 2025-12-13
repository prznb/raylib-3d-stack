#pragma once
#include "program_manager.hpp"
#include "raylib.h"
#include <nlohmann/json_fwd.hpp>
#include <raylib-cpp.hpp>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "core/camera_handler.hpp"
#include "core/gui_handler.hpp"
#include "core/input_event_handler.hpp"
#include "core/physics_world.hpp"
#include "core/renderer_scene.hpp"
#include "core/shared_state.hpp"
#include "core/physics_shaper.hpp"
//#include "modules/third-party/entt.hpp"


/**
 * @brief Main program handler. Integrates all the sub-components.
 */
class ProgramHandler {
public:
  ProgramHandler();
  ~ProgramHandler() = default;

  void run();

private:
  // Core
  Shared _ss;
  raylib::Window _w;
  CameraHandler _cc;
  renderer::Scene _r;
  InputEventHandler _ieh;
  physics::World _dw;
  physics::Shaper _s;
  gui::Handler _gh;
  RenderTexture2D _target;
  Shader _shader; 

  // Management
  ProgramManager _m;

  // Member f
  void draw();
  void process();
};