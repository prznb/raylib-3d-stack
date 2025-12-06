#include "physics_bridge.hpp"
#include "LinearMath/btTransform.h"
#include "shared_state.hpp"
#include <vector>


namespace physics {

void Bridge::process(SharedState& state) {
  poseTranslate(state);
}

void Bridge::poseTranslate(SharedState &state) {
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

} // namespace physics