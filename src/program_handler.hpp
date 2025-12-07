#pragma once
#include <raylib-cpp.hpp>

#include "core/camera_handler.hpp"
#include "core/gui_handler.hpp"
#include "core/input_event_handler.hpp"
#include "core/physics_world.hpp"
#include "core/renderer.hpp"
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
  SharedState _ss;
  raylib::Window _w;
  CameraHandler _cc;
  renderer::Scene _r;
  InputEventHandler _ieh;
  physics::World _dw;
  physics::Shaper _s;
  gui::Handler _gh;
};