#pragma once
#include "physics_world.hpp"
#include "BulletCollision/CollisionShapes/btCylinderShape.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "LinearMath/btAlignedObjectArray.h"
#include "LinearMath/btScalar.h"
#include "LinearMath/btVector3.h"
#include "raylib.h"
#include "raymath.h"
#include "shared_state.hpp"
#include "types.hpp"
#include <cstdlib>
#include <utility>

namespace physics {
World::World() {
  // Boilerplate Bullet Physics initialization
  // Reference:
  // https://github.com/bulletphysics/bullet3/blob/master/examples/HelloWorld/HelloWorld.cpp
  collisionConfiguration = new btDefaultCollisionConfiguration();
  dispatcher = new btCollisionDispatcher(collisionConfiguration);
  overlappingPairCache = new btDbvtBroadphase();
  solver = new btSequentialImpulseConstraintSolver;
  dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache,
                                              solver, collisionConfiguration);
  dynamicsWorld->setGravity(btVector3(0, -10, 0));
}

World::~World() {
  // remove the rigidbodies from the dynamics world and delete them
  for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--) {
    btCollisionObject *obj = dynamicsWorld->getCollisionObjectArray()[i];
    btRigidBody *body = btRigidBody::upcast(obj);
    if (body && body->getMotionState()) {
      delete body->getMotionState();
    }
    dynamicsWorld->removeCollisionObject(obj);
    delete obj;
  }

  // delete collision shapes
  for (int j = 0; j < collisionShapes.size(); j++) {
    btCollisionShape *shape = collisionShapes[j];
    collisionShapes[j] = 0;
    delete shape;
  }
  delete dynamicsWorld;
  delete solver;
  delete overlappingPairCache;
  delete dispatcher;
  delete collisionConfiguration;
}

void World::setup(Shared &state) 
{
  state.vehicle = vehicle_interfaces[state.selected_vehicle].second;
}

void World::addObject(nlohmann::json &obj_params) {
  // create a dynamic rigidbody
  btCollisionShape *colShape;
  if (obj_params["type"] == "ground" || obj_params["type"] == "cube") {
    btVector3 dim = {(float)(obj_params["dimensions"]["width"]) / 2.f,
                     (float)(obj_params["dimensions"]["height"]) / 2.f,
                     (float)(obj_params["dimensions"]["length"]) / 2.f};
    colShape = new btBoxShape(dim);
  } 
  else if (obj_params["type"] == "sphere") {
    btScalar radius = obj_params["dimensions"]["radius"];
    colShape = new btSphereShape(radius);
  } else if (obj_params["type"] == "cylinder") {
    btVector3 dim = {
        abs((float)(obj_params["dimensions"]
                              ["radius"])), // radius == half-extent
        abs((float)(obj_params["dimensions"]["height"]) / 2.f),
        abs((float)(obj_params["dimensions"]["radius"]))};
    colShape = new btCylinderShape(dim);
  }

  else if (obj_params["type"] == "car") {
    btVector3 dim = {
        (float)(obj_params["dimensions"]["chassis"]["width"]) / 2.f,
        (float)(obj_params["dimensions"]["chassis"]["height"]) / 2.f,
        (float)(obj_params["dimensions"]["chassis"]["length"]) / 2.f};
    colShape = new btBoxShape(dim);
  }

  collisionShapes.push_back(colShape);

  /// Create Dynamic Objects
  btTransform startTransform;
  startTransform.setIdentity();

  btScalar mass(obj_params["mass"]);

  // rigidbody is dynamic if and only if mass is non zero, otherwise static
  bool isDynamic = (mass != 0.f);

  btVector3 localInertia = {obj_params["inertia"]["x"],
                            obj_params["inertia"]["y"],
                            obj_params["inertia"]["z"]};

  if (isDynamic)
    colShape->calculateLocalInertia(mass, localInertia);

  btVector3 position = {obj_params["position"]["x"],
                        obj_params["position"]["y"],
                        obj_params["position"]["z"]};
  startTransform.setOrigin(position);

  static btQuaternion q_init;
  q_init.setEulerZYX(obj_params["rotation"]["yaw"],
                     obj_params["rotation"]["pitch"],
                     obj_params["rotation"]["roll"]);
  startTransform.setRotation(q_init);

  // using motionstate is recommended, it provides interpolation capabilities,
  // and only synchronizes 'active' objects
  btDefaultMotionState *myMotionState =
      new btDefaultMotionState(startTransform);
  btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape,
                                                  localInertia);
  
  if(obj_params["type"] == "ground")
  {
    rbInfo.m_friction = 1.5f;
  }

  btRigidBody *body = new btRigidBody(rbInfo);

  dynamicsWorld->addRigidBody(body);
  renderer_object_representations.base_transforms.push_back(
      RendererObjectTransform());

  if (obj_params["type"] == "car") {
    vehicleSetup(body, obj_params);
  }
}

void World::vehicleSetup(btRigidBody *body, nlohmann::json &obj_params) {
  body->setActivationState(DISABLE_DEACTIVATION);
  btVehicleRaycaster *raycaster = new btDefaultVehicleRaycaster(dynamicsWorld);
  btRaycastVehicle::btVehicleTuning tuning;

  btRaycastVehicle *vehicle = new btRaycastVehicle(tuning, body, raycaster);
  dynamicsWorld->addAction(vehicle);

  vehicle->setCoordinateSystem(0, 1, 2);

  // add wheels
  btScalar suspensionRestLength =
      obj_params["dimensions"]["wheels"]["suspension_at_rest"];
  btScalar wheelRadius = obj_params["dimensions"]["wheels"]["radius"];

  btScalar wheelbase = obj_params["dimensions"]["wheels"]["wheelbase"];
  btScalar track = obj_params["dimensions"]["wheels"]["track"];

  btVector3 wheelDirectionCS0 = {0, -1, 0};             // down
  btVector3 wheelAxleCSLeft = {-wheelbase / 2.f, 0, 0}; // left
  btVector3 wheelAxleCSRight = {wheelbase / 2.f, 0, 0}; // right

  btVector3 connectionPointCS0FL = {-track / 2.f, 0.f, wheelbase / 2.f};
  btVector3 connectionPointCS0FR = {track / 2.f, 0.f, wheelbase / 2.f};
  btVector3 connectionPointCS0RL = {-track / 2.f, 0.f, -wheelbase / 2.f};
  btVector3 connectionPointCS0RR = {track / 2.f, 0.f, -wheelbase / 2.f};

  // FL
  vehicle->addWheel(connectionPointCS0FL, wheelDirectionCS0, wheelAxleCSLeft,
                    suspensionRestLength, wheelRadius, tuning, true);
  // FR
  vehicle->addWheel(connectionPointCS0FR, wheelDirectionCS0, wheelAxleCSRight,
                    suspensionRestLength, wheelRadius, tuning, true);
  // RL
  vehicle->addWheel(connectionPointCS0RL, wheelDirectionCS0, wheelAxleCSLeft,
                    suspensionRestLength, wheelRadius, tuning, false);
  // RR
  vehicle->addWheel(connectionPointCS0RR, wheelDirectionCS0, wheelAxleCSRight,
                    suspensionRestLength, wheelRadius, tuning, false);

  // tuning
  for (int i = 0; i < vehicle->getNumWheels(); i++) {
    btWheelInfo &wheel = vehicle->getWheelInfo(i);
    wheel.m_suspensionStiffness = 20.35f;
    wheel.m_wheelsDampingRelaxation = 50.0f;
    wheel.m_wheelsDampingCompression = 30.0f;
    wheel.m_frictionSlip = 500.f;
    wheel.m_rollInfluence = 0.0f;
  }

  // Add tracker: most recently added obj (vehicle collider), and the interface
  // for the pointer
  int base_vehicle_object_index =
      renderer_object_representations.base_transforms.size() - 1;

  // Register index and handle for the vehicle interface
  vehicle_interfaces.push_back(
      std::make_pair(base_vehicle_object_index, vehicle));

  // add placeholder transforms for the wheels
  for (int i = 0; i < 4; ++i) {
    renderer_object_representations.subtransforms[base_vehicle_object_index]
        .push_back(RendererObjectTransform());
  }
}

void World::applyVehicleControls(const ExternalFT &eft) {
  // vehicle->applyEngineForce(engineForce, wheelIndex);
  // vehicle->setBrake(brakeForce, wheelIndex);
  // vehicle_interfaces[0].second->setSteeringValue(0.3, 0);
  // vehicle_interfaces[0].second->setSteeringValue(0.3, 1);
  // vehicle_interfaces[0].second->applyEngineForce(3E3, 2);
  // vehicle_interfaces[0].second->applyEngineForce(3E3, 3);
}

void World::process(Shared &state, const ExternalFT &eft) {
  applyVehicleControls(eft);
  dynamicsWorld->stepSimulation(1.f / 60.f, 10);
  translateObjectTransforms(state);     // all objects
  translateAdditionalTransforms(state); // interfaces and additional
}

RendererObjectRepresentations &World::next() {
  return renderer_object_representations;
}

void World::save() {
  // From the SDK manual:
  btDefaultSerializer *serializer = new btDefaultSerializer();
  this->dynamicsWorld->serialize(serializer);
  FILE *file = fopen("testFile.bullet", "wb");
  fwrite(serializer->getBufferPointer(), serializer->getCurrentBufferSize(), 1,
         file);
  fclose(file);
}

// Intermal member functions
void World::translateObjectTransforms(Shared &state) {

  static RendererObjectTransform rendererside_transform;

  for (int i = 0; i < dynamicsWorld->getCollisionObjectArray().size(); ++i) {
    btCollisionObject *obj = dynamicsWorld->getCollisionObjectArray()[i];
    btRigidBody *body = btRigidBody::upcast(obj);
    btTransform trans_physics;

    if (body && body->getMotionState()) {
      body->getMotionState()->getWorldTransform(trans_physics);
    } else {
      trans_physics = obj->getWorldTransform();
    }

    rendererside_transform.wf_translation =
        Vector3{trans_physics.getOrigin().x(), trans_physics.getOrigin().y(),
                trans_physics.getOrigin().z()};

    trans_physics.getRotation().getEulerZYX(
        rendererside_transform.wf_rotation.z,
        rendererside_transform.wf_rotation.y,
        rendererside_transform.wf_rotation.x);

    renderer_object_representations.base_transforms[i] = rendererside_transform;
  }
}

void World::translateAdditionalTransforms(Shared &state) {
  // vehicles
  for (auto &v : vehicle_interfaces) {
    int base_collider_idx = v.first;
    auto vehicle_ifc = v.second;

    // TODO: obtain offsets for the wheel positions and orientations in the
    // chassis frame
    //       ... any frame will be good ....

    auto info_fl = vehicle_ifc->getWheelInfo(0);
    auto info_fr = vehicle_ifc->getWheelInfo(1);
    auto info_rl = vehicle_ifc->getWheelInfo(2);
    auto info_rr = vehicle_ifc->getWheelInfo(3);

    renderer_object_representations.subtransforms[base_collider_idx][0] =
        convertWheelInfo(info_fl);
    renderer_object_representations.subtransforms[base_collider_idx][1] =
        convertWheelInfo(info_fr);
    renderer_object_representations.subtransforms[base_collider_idx][2] =
        convertWheelInfo(info_rl);
    renderer_object_representations.subtransforms[base_collider_idx][3] =
        convertWheelInfo(info_rr);
  }
}

Vector3 World::convertVec3(const btVector3 &bt_vec3) {
  return (Vector3){bt_vec3.getX(), bt_vec3.getY(), bt_vec3.getZ()};
}

RendererObjectTransform World::convertWheelInfo(const btWheelInfo &bt_winfo) {
  RendererObjectTransform rot;

  btVector3 tireCenterPoint =
      bt_winfo.m_raycastInfo.m_contactPointWS +
      bt_winfo.m_wheelsRadius * bt_winfo.m_raycastInfo.m_contactNormalWS;
  rot.wf_translation =
      convertVec3(tireCenterPoint); //.m_worldTransform.getOrigin());
  bt_winfo.m_worldTransform.getRotation().getEulerZYX(
      rot.wf_rotation.z, rot.wf_rotation.y, rot.wf_rotation.x);
  return rot;
}

} // namespace physics