#pragma once
#include "LinearMath/btVector3.h"
#include "raylib.h"
#include "shared_state.hpp"
#include "types.hpp"
#include <memory>

/** @brief Apply external forces and torques to the objects
 *
 * ref:
 * https://stackoverflow.com/questions/1677059/bullet-physics-apply-torque-impulse-in-bodys-local-space
 *
 * @todo Fix it - it should be handled by the bullet control interfaces instead
 */
namespace physics {

class Shaper {
  Vector3 _capture_for_impulse;
  Vector3 _capture_for_torques;

  btVector3 _impulse_direction;
  btVector3 _torque_direction;

  float _impulse_force;
  float _torque;

  ExternalFT _eft;
  
  void captureInput();
  void zeroAll(Shared &state);

public:
  Shaper();

  void process(Shared &state);
  const ExternalFT& next();


};

} // namespace physics