#pragma once
#include "btBulletDynamicsCommon.h"
#include "raylib.h"

namespace physics {

class Bridge {
public:
  Transform computeObjectTransformForRenderer(btCollisionObject *obj);
};
}