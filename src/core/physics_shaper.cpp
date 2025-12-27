#include "physics_shaper.hpp"
#include "raymath.h"
#include "shared_state.hpp"
#include "types.hpp"


namespace physics 
{
// Public
Shaper::Shaper() : _steering_dynamics(0.1f), _acceleration_dynamics(0.5f)
{
  // TODO: Fix it, should be done programmatically
  // Add placeholder variable for one vehicle
  _eft.vehicle_controls.push_back(VehicleControls());
}

void Shaper::process(Shared &state) 
{
  if(*state.camera_view != PLAYER) return; 

  float engine_force_max = 1E3f;
  float steering_angle_max = 0.45f;

  // Compute controls from the user input
  float engine_force_inst = _acceleration_dynamics.step(engine_force_max*state.is->lin_x);
  float steering_angle_inst = _steering_dynamics.step(steering_angle_max*(-1.f)*state.is->lin_y);

  _eft.vehicle_controls[state.selected_vehicle].setpoint_engine_force = engine_force_inst;
  _eft.vehicle_controls[state.selected_vehicle].setpoint_steering_angle = steering_angle_inst;
}

const ExternalFT& Shaper::next()
{
  return _eft;
}


} // namespace physics