#pragma once
#include "physics_world.hpp"
#include "LinearMath/btAlignedObjectArray.h"
#include "shared_state.hpp"
#include <iostream>
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

void World::setup(SharedState& state) {
  addGround(state);
}

void World::addObject(SharedState& state) {
  // create a dynamic rigidbody

  btCollisionShape *colShape = new btBoxShape(btVector3(2.5f, 2.5f, 2.5f));
  // btCollisionShape *colShape = new btSphereShape(btScalar(1.));
  collisionShapes.push_back(colShape);

  /// Create Dynamic Objects
  btTransform startTransform;
  startTransform.setIdentity();


  btScalar mass(10);

  // rigidbody is dynamic if and only if mass is non zero, otherwise static
  bool isDynamic = (mass != 0.f);

  btVector3 localInertia(10.f, 10.f, 10.f);
  if (isDynamic)
    colShape->calculateLocalInertia(mass, localInertia);

  startTransform.setOrigin(btVector3(0,rand()%21, 1));
  static btQuaternion q_init;
  q_init.setEulerZYX(0.f, 0.f, 1.f);
  startTransform.setRotation(q_init);

  // using motionstate is recommended, it provides interpolation capabilities,
  // and only synchronizes 'active' objects
  btDefaultMotionState *myMotionState =
      new btDefaultMotionState(startTransform);
  btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape,
                                                  localInertia);
  btRigidBody *body = new btRigidBody(rbInfo);

  dynamicsWorld->addRigidBody(body);
  state.object_poses_physics.push_back(startTransform);
}

void World::addGround(SharedState& state){
  btCollisionShape *groundShape =
      new btBoxShape(btVector3(btScalar(500.), btScalar(500.), btScalar(500.)));

  collisionShapes.push_back(groundShape);

  btTransform groundTransform;
  groundTransform.setIdentity();
  groundTransform.setOrigin(btVector3(-250, -500, -250));

  btScalar mass(0.);

  // rigidbody is dynamic if and only if mass is non zero, otherwise static
  bool isDynamic = (mass != 0.f);

  btVector3 localInertia(0, 0, 0);
  if (isDynamic)
    groundShape->calculateLocalInertia(mass, localInertia);

  // using motionstate is optional, it provides interpolation capabilities,
  // and only synchronizes 'active' objects
  btDefaultMotionState *myMotionState =
      new btDefaultMotionState(groundTransform);
  btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState,
                                                  groundShape, localInertia);
  btRigidBody *body = new btRigidBody(rbInfo);

  // add the body to the dynamics world
  dynamicsWorld->addRigidBody(body);
  state.object_poses_physics.push_back(groundTransform);
}

void World::process(SharedState &state) {
  dynamicsWorld->stepSimulation(1.f / 60.f, 10);
  updateObjectTransforms(state);
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

}