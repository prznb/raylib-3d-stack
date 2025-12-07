#pragma once

// Bullet 
#include "LinearMath/btVector3.h"
#include "LinearMath/btAlignedObjectArray.h"
#include "LinearMath/btTransform.h"

// Raylib
#include "raylib.h"


// std C++
#include <memory>
#include <vector>
#include <iostream>

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

/**
* @brief Program-wide accessible collection of common states.
*
* @todo Fix it. It's probably an anti-pattern.
*/
struct SharedState 
{
  SharedState(){};
  ~SharedState() = default;

  // Functions
  void registerEvent(Event ev)
  {
    switch (ev) {
      case OBJECT_ADDED:
        object_poses_renderer.push_back(RendererObjectTransform());
        object_poses_physics.push_back(btTransform());
      break;

      default:
      return;
    }
  }

  // Debug
  bool debug = false;

  // Which subsystem is currently controlling the input
  InputOwner io = SHAPER;

  // Object Representations
  std::vector<RendererObjectTransform> object_poses_renderer;
  std::vector<btTransform> object_poses_physics;

  // Physics setpoint forces 
  std::vector<std::pair<int, btVector3>> external_object_forces; 
  std::vector<std::pair<int, btVector3>> external_object_torques;

  // Quick lookup
  RendererObjectTransform selected_object_pose;


  void verify()
  {
    std::cout << "DEBUG: RENDERER AND PHYSICS OBJECT COUNT: " << object_poses_renderer.size() << " " <<  object_poses_physics.size() << std::endl;
  }
};
