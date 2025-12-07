#pragma once
#include "physics_world.hpp"
#include "LinearMath/btAlignedObjectArray.h"
#include "LinearMath/btVector3.h"
#include "shared_state.hpp"
#include <cstdlib>

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

void World::setup(SharedState& state) {}

void World::addObject(nlohmann::json& obj_params) {
  // create a dynamic rigidbody
  btVector3 dim = {(float)obj_params["side_length"]/2.f,(float)obj_params["side_length"]/2.f,(float)obj_params["side_length"]/2.f};
  btCollisionShape *colShape = new btBoxShape(dim);
  // btCollisionShape *colShape = new btSphereShape(btScalar(1.));
  collisionShapes.push_back(colShape);

  /// Create Dynamic Objects
  btTransform startTransform;
  startTransform.setIdentity();

  btScalar mass(obj_params["mass"]);

  // rigidbody is dynamic if and only if mass is non zero, otherwise static
  bool isDynamic = (mass != 0.f);

  btVector3 localInertia = {obj_params["inertia"],obj_params["inertia"],obj_params["inertia"]};

  if (isDynamic)
    colShape->calculateLocalInertia(mass, localInertia);

  btVector3 position = {obj_params["position"]["x"], obj_params["position"]["y"], obj_params["position"]["z"]};
  startTransform.setOrigin(position);

  static btQuaternion q_init;
  q_init.setEulerZYX(obj_params["rotation"]["yaw"], obj_params["rotation"]["pitch"], obj_params["rotation"]["roll"]);
  startTransform.setRotation(q_init);

  // using motionstate is recommended, it provides interpolation capabilities,
  // and only synchronizes 'active' objects
  btDefaultMotionState *myMotionState =
      new btDefaultMotionState(startTransform);
  btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape,
                                                  localInertia);
  btRigidBody *body = new btRigidBody(rbInfo);

  dynamicsWorld->addRigidBody(body);
}


void World::process(SharedState &state) {
  dynamicsWorld->stepSimulation(1.f / 60.f, 10);
  updateObjectTransforms(state);
  translateObjectTransforms(state);
}



// Intermal member functions

void World::updateObjectTransforms(SharedState& state)
{
    for (int j = 0; j < state.object_poses_physics.size(); j++) {
    btCollisionObject *obj = dynamicsWorld->getCollisionObjectArray()[j];
    btRigidBody *body = btRigidBody::upcast(obj);
    btTransform trans;

    if (body && body->getMotionState()) {
      body->getMotionState()->getWorldTransform(trans);
    } else {
      trans = obj->getWorldTransform();
    }
    state.object_poses_physics[j] = trans;
  }
}

void World::translateObjectTransforms(SharedState &state) 
{
  RendererObjectTransform rendererside_transform;

  for (int i = 0; i < state.object_poses_physics.size(); ++i)
  { 
    btTransform trans_physics = state.object_poses_physics[i];

    rendererside_transform.wf_translation =
        Vector3{trans_physics.getOrigin().x(), trans_physics.getOrigin().y(),
                trans_physics.getOrigin().z()};

    trans_physics.getRotation().getEulerZYX(
        rendererside_transform.wf_rotation.z,
        rendererside_transform.wf_rotation.y,
        rendererside_transform.wf_rotation.x);
    
    state.object_poses_renderer[i] = rendererside_transform;
    
  }
}

}