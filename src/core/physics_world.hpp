#pragma once
#include "BulletDynamics/Vehicle/btVehicleRaycaster.h"
#include "BulletDynamics/Vehicle/btWheelInfo.h"
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
  void save();

  RendererObjectRepresentations& next();

private:
  // Internal member functions
  void translateObjectTransforms(Shared& state);
  void translateAdditionalTransforms(Shared& state);
  void applyVehicleControls(Shared& state, const ExternalFT& eft);

  // Utils
  Vector3 convertVec3(const btVector3& bt_vec3);
  RendererObjectTransform convertWheelInfo(const btWheelInfo& bt_winfo);
  
  // Interfaces
  void vehicleSetup(btRigidBody* body, nlohmann::json& obj_params);

  // Bullet Physics World
  btDefaultCollisionConfiguration *collisionConfiguration;
  btCollisionDispatcher *dispatcher;
  btBroadphaseInterface *overlappingPairCache;
  btSequentialImpulseConstraintSolver *solver;
  btDiscreteDynamicsWorld *dynamicsWorld;
  btAlignedObjectArray<btCollisionShape *> collisionShapes;

  // Compat
  RendererObjectRepresentations renderer_object_representations;
  // Comm/Internal
  std::vector<std::pair<int, btRaycastVehicle *>> vehicle_interfaces;

};
} // namespace physics