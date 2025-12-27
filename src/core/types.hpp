#pragma once 
#include "LinearMath/btScalar.h"
#include "raylib.h"
#include <unordered_map>
#include <vector>
#include "LinearMath/btVector3.h"
#include <nlohmann/json.hpp>


using json = nlohmann::json;

// Events
typedef enum Event{
  OBJECT_ADDED = 0,
}Event;


// Input
class AnalogAxis
{
  float _val;
  const float _LIMIT_UPPER = 1.0f;
  const float _LIMIT_LOWER = -1.0f;
  //GamepadAxis _which;

  public:
  AnalogAxis()
  {
    //_which = reference_axis;
  }
  AnalogAxis operator=(float fval)
  {
    AnalogAxis ret;
    ret.set(fval);
    return ret;
  }

  float get() const
  {
    return _val;
  }

  void set(float newVal)
  {
    if (newVal>_LIMIT_UPPER) _val = 1.0f;
    else if (newVal<_LIMIT_LOWER) _val = -1.0f;
    else _val = newVal;
  } 
};


typedef enum InputMode{
  CAMERA = 0,
  CAMERA_LOCK,
  PLAYER, 
  SHAPER
}InputMode;

typedef struct InputStorage{
  // Axes 
  float lin_x;
  float lin_y;
  float lin_z;
  float rot_x;
  float rot_y;
  float rot_z; 

  bool kbd_c; 
  bool kbd_v; 
  bool kbd_b;
  bool kbd_space;

  float mou_s; 

}InputStorage;


typedef struct RendererObjectTransform{
    Vector3 wf_translation = {0.f, 0.f, 0.f};    // Translation in world frame
    Vector3 wf_rotation = {0.f, 0.f, 0.f};    // Rotation in world frame
}RendererObjectTransform;

typedef struct RendererObjectRepresentations
{
  std::vector<RendererObjectTransform> base_transforms; // World-frame representation of a compound object - its base
  std::unordered_map<int, std::vector<RendererObjectTransform>> subtransforms; // Collection of subsequent transforms for compound objects
}RendererObjectRepresentations;

typedef struct VehicleControls{
  btScalar setpoint_engine_force;
  btScalar setpoint_steering_angle;
  btScalar setpoint_braking_force;
}VehicleControls;

typedef struct ExternalFT
{
  std::vector<std::pair<int, btVector3>> external_object_forces; 
  std::vector<std::pair<int, btVector3>> external_object_torques;
  
  // Vehicles
  std::vector<VehicleControls> vehicle_controls;
} ExternalFT;



