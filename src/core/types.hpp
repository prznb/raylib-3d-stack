#pragma once 
#include "raylib.h"
#include <vector>
#include "LinearMath/btVector3.h"

typedef enum Event{
  OBJECT_ADDED = 0,
}Event;

typedef enum InputOwner{
  CAMERA = 0,
  PLAYER, 
  SHAPER
}InputOwner;

typedef struct RendererObjectTransform{
    Vector3 wf_translation = {0.f, 0.f, 0.f};    // Translation in world frame
    Vector3 wf_rotation = {0.f, 0.f, 0.f};    // Rotation in world frame
}RendererObjectTransform;

typedef struct ExternalFT
{
  std::vector<std::pair<int, btVector3>> external_object_forces; 
  std::vector<std::pair<int, btVector3>> external_object_torques;
} ExternalFT;