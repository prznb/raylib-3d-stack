#include "physics_shaper.hpp"

/** @brief Apply forces and torquest to the object
 *
 * ref:
 * https://stackoverflow.com/questions/1677059/bullet-physics-apply-torque-impulse-in-bodys-local-space
 */
namespace physics {

// Private
void Shaper::captureInput() {
  _capture_for_impulse.x = (IsKeyDown(KEY_A) - IsKeyDown(KEY_D));
  _capture_for_impulse.y =
      (IsKeyDown(KEY_LEFT_SHIFT) - IsKeyDown(KEY_LEFT_CONTROL));
  _capture_for_impulse.z = (IsKeyDown(KEY_W) - IsKeyDown(KEY_S));

  _capture_for_torques.x = (IsKeyDown(KEY_UP) - IsKeyDown(KEY_DOWN));
  _capture_for_torques.y = (IsKeyDown(KEY_Q) - IsKeyDown(KEY_E));
  _capture_for_torques.z = (IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT));
}

// Public
Shaper::Shaper() {
  _impulse_direction.setZero();
  _torque_direction.setZero();
  _impulse_force = 1E4;
  _torque = 1E3;
  _capture_for_impulse = Vector3Zero();
  _capture_for_torques = Vector3Zero();
}

void Shaper::process(SharedState &state) {
  if (state.io != SHAPER) {
    state.player_force_input.setZero();
    state.player_torque_input.setZero();
    _capture_for_impulse = Vector3Zero();
    _capture_for_torques = Vector3Zero();
    _impulse_direction.setZero();
    _torque_direction.setZero();
    return;
  }

  captureInput();

  // Compute correction:
  _impulse_direction.setX(_capture_for_impulse.x);
  _impulse_direction.setY(_capture_for_impulse.y);
  _impulse_direction.setZ(_capture_for_impulse.z);
  _impulse_direction.norm();

  _torque_direction.setX(_capture_for_torques.x);
  _torque_direction.setY(_capture_for_torques.y);
  _torque_direction.setZ(_capture_for_torques.z);
  _torque_direction.norm();

  state.player_force_input = _impulse_direction * _impulse_force;
  state.player_torque_input = _torque_direction * _torque;
}

} // namespace physics