#pragma once
#include <raylib-cpp.hpp>

#include "modules/camera_handler.hpp"
#include "modules/gui_handler.hpp"
#include "modules/input_event_handler.hpp"
#include "modules/physics_world.hpp"
#include "modules/renderer.hpp"
#include "modules/shared_state.hpp"
#include "modules/physics_shaper.hpp"
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
  // Member variables
  SharedState _state;
  raylib::Window _window_handler;
  CameraHandler _camera_handler;
  renderer::Scene _renderer_scene;
  InputEventHandler _input_events;
  physics::World _bullet_physics;
  physics::Shaper _bullet_physics_ext_interface;
  gui::Handler _gui;
};