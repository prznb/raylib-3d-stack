#pragma once
#include "LinearMath/btVector3.h"
#include "raylib.h"
#include "btBulletDynamicsCommon.h"
#include "raymath.h"

typedef enum InputOwner{
  CAMERA = 0,
  PLAYER, 
  SHAPER
}InputOwner;

/**
* @brief Program-wide accessible collection of common states.
*
* @todo Fix it. It's probably an anti-pattern.
*/
struct SharedState 
{
  // Debug
  bool debug = true;

  // Which subsystem is currently controlling the input
  InputOwner io = SHAPER;

  // Renderer Representation
  Transform current_player_pose;

  Vector3 getCurrentPlayerRotationEuler()
  {
    return QuaternionToEuler(current_player_pose.rotation);
  }

  // Physics setpoint forces
  btVector3 player_force_input{0.f, 0.f,0.f}; 
  btVector3 player_torque_input{0.f, 0.f,0.f};;

};
