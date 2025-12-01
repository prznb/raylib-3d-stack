#pragma once
#include "physics_bridge.hpp"
#include "physics_shaper.hpp"
#include "shared_state.hpp"

namespace physics
{
class World {

  Bridge& _pb;
  Shaper& _s;

public:
  World(Shaper& shaper, Bridge& bridge): _s(shaper), _pb(bridge) {
    // Boilerplate Bullet Physics initialization
    // Reference:
    // https://github.com/bulletphysics/bullet3/blob/master/examples/HelloWorld/HelloWorld.cpp
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    overlappingPairCache = new btDbvtBroadphase();
    solver = new btSequentialImpulseConstraintSolver;
    dynamicsWorld = new btDiscreteDynamicsWorld(
        dispatcher, overlappingPairCache, solver, collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0, -10, 0));
  };
  ~World() {
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
  void setup() {
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
  }

  void addObject() 
  {
    // create a dynamic rigidbody

    btCollisionShape *colShape = new btBoxShape(btVector3(40.f, 5.f, 30.f));
    // btCollisionShape *colShape = new btSphereShape(btScalar(1.));
    collisionShapes.push_back(colShape);

    /// Create Dynamic Objects
    btTransform startTransform;
    startTransform.setIdentity();

    btScalar mass(5E2);

    // rigidbody is dynamic if and only if mass is non zero, otherwise static
    bool isDynamic = (mass != 0.f);

    btVector3 localInertia(100.f, 100.f, 100.f);
    if (isDynamic)
      colShape->calculateLocalInertia(mass, localInertia);

    startTransform.setOrigin(btVector3(0, 100, 0));
    static btQuaternion q_init;
    q_init.setEulerZYX(1.f, 0.f, 0.f);
    startTransform.setRotation(q_init);

    // using motionstate is recommended, it provides interpolation capabilities,
    // and only synchronizes 'active' objects
    btDefaultMotionState *myMotionState =
        new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState,
                                                    colShape, localInertia);
    btRigidBody *body = new btRigidBody(rbInfo);

    dynamicsWorld->addRigidBody(body);
  }

  void process(SharedState &state) {

    dynamicsWorld->stepSimulation(1.f / 60.f, 10);

    // print positions of all objects
    for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--) {
      btCollisionObject *obj = dynamicsWorld->getCollisionObjectArray()[j];
      btRigidBody *body = btRigidBody::upcast(obj);
      btTransform trans;
      if (body && body->getMotionState()) {
        body->getMotionState()->getWorldTransform(trans);
      } else {
        trans = obj->getWorldTransform();
      }
      printf("world orientation object %d = %f,%f,%f\n", j,
             float(trans.getRotation().getX()),
             float(trans.getRotation().getY()),
             float(trans.getRotation().getZ()));
    }

    // Retrieve player state and apply force for the next iteration
    btCollisionObject *obj =dynamicsWorld->getCollisionObjectArray()[1]; // test -> player collision obj.
    state.current_player_pose = _pb.computeObjectTransformForRenderer(obj);
    btRigidBody *body = btRigidBody::upcast(obj);
    body->applyCentralImpulse(state.player_force_input);
    body->applyTorqueImpulse(state.player_torque_input);
    
  }

  btTransform getObjectPoseAtIndexInDynamicsWorld(int index) {
    btCollisionObject *obj = dynamicsWorld->getCollisionObjectArray()[index];
    btRigidBody *body = btRigidBody::upcast(obj);
    btTransform trans;
    if (body && body->getMotionState()) {
      body->getMotionState()->getWorldTransform(trans);
    } else {
      trans = obj->getWorldTransform();
    }
    return trans;
  }

private:
  btDefaultCollisionConfiguration *collisionConfiguration;
  btCollisionDispatcher *dispatcher;
  btBroadphaseInterface *overlappingPairCache;
  btSequentialImpulseConstraintSolver *solver;
  btDiscreteDynamicsWorld *dynamicsWorld;
  btAlignedObjectArray<btCollisionShape *> collisionShapes;
};
}