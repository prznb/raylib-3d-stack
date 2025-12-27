#pragma once
#include "LinearMath/btVector3.h"
#include "raylib.h"
#include "shared_state.hpp"
#include "types.hpp"
#include <memory>


namespace physics {

class DynamicsFirstOrder {
  float _y, _y_prev;
  float _a;

public:
  DynamicsFirstOrder(float a) {
    _a = a;
    _y_prev = 0.f;
  }

  float step(float x) {
    _y = _a * x + (1.f - _a) * _y_prev;
    _y_prev = _y;
    return _y;
  }
};

class Shaper {
  ExternalFT _eft;

  DynamicsFirstOrder _steering_dynamics;
  DynamicsFirstOrder _acceleration_dynamics;

  float responseFirstOrderSystem(float setpoint, float current);

public:
  Shaper();

  void process(Shared &state);
  const ExternalFT &next();
};

} // namespace physics