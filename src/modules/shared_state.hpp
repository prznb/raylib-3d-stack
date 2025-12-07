#pragma once

// Bullet 
#include "LinearMath/btVector3.h"
#include "LinearMath/btAlignedObjectArray.h"
#include "LinearMath/btTransform.h"

// Raylib
#include "raylib.h"


// std C++
#include <memory>
#include <unordered_map>
#include <variant>
#include <vector>
#include <iostream>

typedef enum InputOwner{
  CAMERA = 0,
  PLAYER, 
  SHAPER
}InputOwner;

typedef struct RendererObjectTransform{
    Vector3 wf_translation = {0.f, 0.f, 0.f};    // Translation in world frame
    Vector3 wf_rotation = {0.f, 0.f, 0.f};    // Rotation in world frame
}RendererObjectTransform;

/**
* @brief Used to keep track of and initialize object.
* 
* Shared == common representation for the renderer and physics.
* 
*/
class SharedObjectParams
{
  using param_variant_shared = std::variant<std::string, int, float, double>;
  using param_variant_render = std::variant<float, RendererObjectTransform, Color>;
  using param_variant_physics = std::variant<btScalar,btVector3>;

  std::unordered_map<std::string, param_variant_shared> _params_shared;
  std::unordered_map<std::string, param_variant_render> _params_render;
  std::unordered_map<std::string, param_variant_physics> _params_physics;

  bool _no_params_assigned = true;

  public:
  SharedObjectParams(){};
  ~SharedObjectParams() = default;

  void constructParamsCube(float edge_length, float pos_x, float pos_y, float pos_z, Color tint)
  {
    if(_no_params_assigned == false)
    {
      return;
    }
    // Assign shared
    _params_shared["TYPE"] = "CUBE";

    // Assign raylib/renderer params
    _params_render["MESH_TINT"] = tint;
    _params_render["POSE"] = RendererObjectTransform{{pos_x, pos_y,pos_z}, {0.f,0.f, 0.f}};
    _params_render["EDGE_LEN"] = edge_length;

    // Assign physics params
    _params_physics["POSITION"] = btVector3{pos_x, pos_y, pos_z};
    _params_physics["EDGE_LEN"] = 0.5f*edge_length;

    _no_params_assigned = false;
  }

  std::unordered_map<std::string, param_variant_shared>& getShared()
  {
    return _params_shared;
  }

  std::unordered_map<std::string, param_variant_render>& getRender()
  {
    return _params_render; 
  }

  std::unordered_map<std::string, param_variant_physics>& getPhysics()
  {
    return _params_physics; 
  }

  bool isEmpty()
  {
    return _no_params_assigned;
  }

};

/**
* @brief Program-wide accessible collection of common states.
*
* @todo Fix it. It's probably an anti-pattern.
*/
struct SharedState 
{
  SharedState(){};
  ~SharedState() = default;

  // Functions

  // Debug
  bool debug = false;

  // Which subsystem is currently controlling the input
  InputOwner io = SHAPER;

  // Object Representations
  std::vector<RendererObjectTransform> object_poses_renderer;
  std::vector<btTransform> object_poses_physics;

  // Physics setpoint forces 
  std::vector<std::pair<int, btVector3>> external_object_forces; 
  std::vector<std::pair<int, btVector3>> external_object_torques;

  // Quick lookup
  RendererObjectTransform selected_object_pose;


  void verify()
  {
    std::cout << "DEBUG: RENDERER AND PHYSICS OBJECT COUNT: " << object_poses_renderer.size() << " " <<  object_poses_physics.size() << std::endl;
  }
};
