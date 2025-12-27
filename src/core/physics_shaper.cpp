#include "physics_shaper.hpp"
#include "raymath.h"
#include "shared_state.hpp"


namespace physics 
{
// Public
Shaper::Shaper()
{

}

void Shaper::process(Shared &state) {
}

const ExternalFT& Shaper::next()
{
  return _eft;
}

} // namespace physics