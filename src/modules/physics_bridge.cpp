#include "physics_bridge.hpp"

namespace physics {

Transform Bridge::computeObjectTransformForRenderer(btCollisionObject *obj) {
  Transform rendererside_transform;

  btRigidBody *body = btRigidBody::upcast(obj);
  btTransform trans;
  if (body && body->getMotionState()) {
    body->getMotionState()->getWorldTransform(trans);
  } else {
    trans = obj->getWorldTransform();
  }

  rendererside_transform.translation = Vector3{
      trans.getOrigin().x(), trans.getOrigin().y(), trans.getOrigin().z()};
  rendererside_transform.rotation =
      Vector4{trans.getRotation().getX(), trans.getRotation().getY(),
              trans.getRotation().getZ(), trans.getRotation().getW()};
  rendererside_transform.scale = Vector3{1.f, 1.f, 1.f};
  return rendererside_transform;
}

} // namespace physics