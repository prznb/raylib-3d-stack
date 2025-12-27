#pragma once
#include "LinearMath/btVector3.h"
#include "raylib.h"
#include "shared_state.hpp"
#include "types.hpp"
#include <memory>

/** @brief Apply external forces and torques to the objects
 *
 * ref:
 *
 * @todo Fix it - it should be handled by the bullet control interfaces instead
 */
namespace physics {

class Shaper {
  ExternalFT _eft;
  
public:
  Shaper();

  void process(Shared &state);
  const ExternalFT& next();


};

} // namespace physics