#pragma once
#include "LinearMath/btAlignedObjectArray.h"
#include "LinearMath/btTransform.h"
#include "physics_bridge.hpp"
#include "physics_shaper.hpp"
#include "shared_state.hpp"
#include <memory>
#include <vector>

namespace physics {
class World {

public:
  World();
  ~World();

  void addObject(SharedState& state);
  void addGround(SharedState& state);
  void setup(SharedState &state);
  void process(SharedState &state);


private:
  // Internal member functions
  void updateObjectTransforms(SharedState& state);

  // Bullet Physics World
  btDefaultCollisionConfiguration *collisionConfiguration;
  btCollisionDispatcher *dispatcher;
  btBroadphaseInterface *overlappingPairCache;
  btSequentialImpulseConstraintSolver *solver;
  btDiscreteDynamicsWorld *dynamicsWorld;
  btAlignedObjectArray<btCollisionShape *> collisionShapes;

};
} // namespace physics