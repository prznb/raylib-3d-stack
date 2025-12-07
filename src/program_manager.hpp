#pragma once
#include "core/physics_world.hpp"
#include "core/renderer_scene.hpp"
#include "core/shared_state.hpp"

class ProgramManager {
  Shared &_shared;
  renderer::Scene &_scene;
  physics::World &_physics;

public:
  ProgramManager(Shared &shared, renderer::Scene &scene,
                 physics::World &physics)
      : _shared(shared), _scene(scene), _physics(physics) {};
  ~ProgramManager() = default;

  void setup() {
    _physics.setup(_shared);
    _scene.setup(_shared);
    _shared.verify();

    spawnGround();
    for (int i = 0; i < 10; ++i) {
      spawnObject();
    }
  }
  void spawnGround() {
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
    obj_params["rotation"]["yaw"] = 0.f;
    obj_params["rotation"]["pitch"] = 0.f;
    obj_params["rotation"]["roll"] = 0.f;

    _scene.addObject(obj_params);
    _physics.addObject(obj_params);
    _shared.registerEvent(OBJECT_ADDED);
  }

  void spawnObject() {
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
    obj_params["rotation"]["yaw"] = 0.f;
    obj_params["rotation"]["pitch"] = 0.f;
    obj_params["rotation"]["roll"] = 1.f;

    _scene.addObject(obj_params);
    _physics.addObject(obj_params);
    _shared.registerEvent(OBJECT_ADDED);
  }
};