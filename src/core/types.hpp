#pragma once 
#include "raylib.h"
#include <unordered_map>
#include <vector>
#include "LinearMath/btVector3.h"
#include <nlohmann/json.hpp>


using json = nlohmann::json;

typedef enum Event{
  OBJECT_ADDED = 0,
}Event;

typedef enum InputOwner{
  CAMERA = 0,
  CAMERA_LOCK,
  PLAYER, 
  SHAPER
}InputOwner;

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

