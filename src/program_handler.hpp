#pragma once
#include "raylib.h"
#include <nlohmann/json_fwd.hpp>
#include <raylib-cpp.hpp>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

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

  void spawnGround()
  {
    // Test Object
    json obj_params;
    
    // Shared Properties
    obj_params["type"] = "cube";
    obj_params["side_length"] = 1E3;
    
    obj_params["color"]["r"] = 0;
    obj_params["color"]["g"] = 0;
    obj_params["color"]["b"] = 255;
    obj_params["color"]["a"] = 255;

    obj_params["mass"] = 0.f;
    obj_params["inertia"] = 0.f;
    //-250, -500, -250
    obj_params["position"]["x"] = -250;
    obj_params["position"]["y"] = -500;
    obj_params["position"]["z"] = -250;
    obj_params["rotation"]["yaw"]   = 0.f;
    obj_params["rotation"]["pitch"]  = 0.f;
    obj_params["rotation"]["roll"] = 0.f;

    _r.addObject(obj_params);
    _dw.addObject( obj_params);
    _ss.registerEvent(OBJECT_ADDED);
  }

  void spawnObject()
  {
    // Test Object
    json obj_params;
    
    // Shared Properties
    obj_params["type"] = "cube";
    obj_params["side_length"] = 5.f;
    
    obj_params["color"]["r"] = 255;
    obj_params["color"]["g"] = 0;
    obj_params["color"]["b"] = 0;
    obj_params["color"]["a"] = 255;

    obj_params["mass"] = 10.f;
    obj_params["inertia"] = 10.f;
    obj_params["position"]["x"] = 0.f;
    obj_params["position"]["y"] = 10.f;
    obj_params["position"]["z"] = 0.f;
    obj_params["rotation"]["yaw"]   = 0.f;
    obj_params["rotation"]["pitch"]  = 0.f;
    obj_params["rotation"]["roll"] = 1.f;


    _r.addObject(obj_params);
    _dw.addObject( obj_params);
    _ss.registerEvent(OBJECT_ADDED);
  }
};