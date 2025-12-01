#pragma once
#include "LinearMath/btVector3.h"
#include "raylib.h"
#include "shared_state.hpp"

/** @brief Apply forces and torquest to the object
 *
 * ref:
 * https://stackoverflow.com/questions/1677059/bullet-physics-apply-torque-impulse-in-bodys-local-space
 */
namespace physics {

class Shaper {
  Vector3 _capture_for_impulse;
  Vector3 _capture_for_torques;

  btVector3 _impulse_direction;
  btVector3 _torque_direction;

  float _impulse_force;
  float _torque;

 // DynamicsController _corrector_altitude;

  void captureInput();

public:
  Shaper();

  void process(SharedState &state);
};

} // namespace physics