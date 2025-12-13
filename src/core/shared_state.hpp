#pragma once

// Vehicle
#include "BulletDynamics/Vehicle/btRaycastVehicle.h"
#include "BulletDynamics/Vehicle/btVehicleRaycaster.h"

// Raylib
#include "raylib.h"

// program
#include "types.hpp"

/**
* @brief Program-wide accessible collection of common states.
*
* @todo Fix it. It's probably an anti-pattern.
*/
struct Shared 
{
  // Debug
  bool debug = true;

  // Which subsystem is currently controlling the input
  InputOwner io = CAMERA_LOCK;

  // Quick lookup
  RendererObjectTransform selected_object_pose;
  Camera* camera;
  btRaycastVehicle* vehicle;

  int selected_vehicle = 0;

  // Functions
  void verify(){}

  void registerEvent(Event ev)
  {
    switch (ev) {
      case OBJECT_ADDED:
      break;
      default:
      return;
    }
  }
};
