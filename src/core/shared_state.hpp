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
  const InputMode* input_mode;

  // Input capture lookup
  const InputStorage* is;

  // Quick lookup
  RendererObjectTransform* selected_object_pose;
  Camera* camera;
  btRaycastVehicle* vehicle;

  int selected_vehicle = 0;
  int selected_vehicle_body_idx = 1;

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
