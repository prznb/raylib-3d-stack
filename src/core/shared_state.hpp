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
  InputOwner io = SHAPER;

  // Quick lookup
  RendererObjectTransform selected_object_pose;

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
