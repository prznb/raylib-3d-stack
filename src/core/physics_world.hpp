#pragma once
#include "btBulletDynamicsCommon.h"
#include "physics_shaper.hpp"
#include "shared_state.hpp"
#include "types.hpp"
#include <memory>
#include <nlohmann/json_fwd.hpp>
#include <vector>
#include <nlohmann/json.hpp>

namespace physics {
class World {

public:
  World();
  ~World();

  void addObject(nlohmann::json& obj_params);
  void setup(Shared &state);
  void process(Shared &state, const ExternalFT& eft);

  const std::vector<RendererObjectTransform>& passover();

  void save() 
  {
    // From the SDK manual:
    btDefaultSerializer* serializer = new btDefaultSerializer();
    this->dynamicsWorld->serialize(serializer);
    FILE* file = fopen("testFile.bullet","wb");
    fwrite(serializer->getBufferPointer(),serializer->getCurrentBufferSize(),1, file);
    fclose(file);
  }

private:
  // Internal member functions
  void translateObjectTransforms(Shared& state);

  // Bullet Physics World
  btDefaultCollisionConfiguration *collisionConfiguration;
  btCollisionDispatcher *dispatcher;
  btBroadphaseInterface *overlappingPairCache;
  btSequentialImpulseConstraintSolver *solver;
  btDiscreteDynamicsWorld *dynamicsWorld;
  btAlignedObjectArray<btCollisionShape *> collisionShapes;

  // Compat
  std::vector<RendererObjectTransform> renderer_object_transforms;

};
} // namespace physics