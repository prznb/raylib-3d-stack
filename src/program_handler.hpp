#pragma once
#include <raylib-cpp.hpp>

#include "modules/camera_handler.hpp"
#include "modules/gui_handler.hpp"
#include "modules/input_event_handler.hpp"
#include "modules/physics_bridge.hpp"
#include "modules/physics_world.hpp"
#include "modules/renderer.hpp"
#include "modules/shared_state.hpp"
#include "modules/physics_shaper.hpp"
#include "modules/third-party/entt.hpp"

/**
 * @brief Main program handler. Integrates all the sub-components.
 */
class ProgramHandler {
public:
  ProgramHandler();
  ~ProgramHandler() = default;

  void run();

private:
  raylib::Window _w;
  SharedState _ss;
  CameraHandler _cc;
  renderer::Scene _r;
  InputEventHandler _ieh;
  physics::World _dw;
  physics::Shaper _s;
  physics::Bridge _pb;
  gui::Handler _gh;
};