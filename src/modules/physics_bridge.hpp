#pragma once
#include "btBulletDynamicsCommon.h"
#include "raylib.h"
#include "shared_state.hpp"

namespace physics {

class Bridge {
public:
  void process(SharedState& state);
  
private: 
  void poseTranslate(SharedState& state);
};

}