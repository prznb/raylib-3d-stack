#pragma once 
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
class InputAxis
{
  float _val;
  const float _LIMIT_UPPER = 1.0f;
  const float _LIMIT_LOWER = -1.0f;
  GamepadAxis _which;

  public:
  InputAxis(GamepadAxis reference_axis)
  {
    _which = reference_axis;
  }

  float get()
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


typedef enum InputOwner{
  CAMERA = 0,
  CAMERA_LOCK,
  PLAYER, 
  SHAPER
}InputOwner;

typedef struct InputStorage{
  // Axes 
  InputAxis lin_X;
  InputAxis lin_Y;
  InputAxis lin_Z;
  InputAxis rot_X;
  InputAxis rot_Y;
  InputAxis rot_Z; 

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

typedef struct ExternalFT
{
  std::vector<std::pair<int, btVector3>> external_object_forces; 
  std::vector<std::pair<int, btVector3>> external_object_torques;
  std::vector<std::pair<int, btVector3>> kinematic_control_direction;
} ExternalFT;

