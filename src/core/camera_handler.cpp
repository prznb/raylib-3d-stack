#include "camera_handler.hpp"
#include "raylib.h"
#include "shared_state.hpp"
#include "types.hpp"

CameraHandler::CameraHandler() {
  _camera.position = {3.0f, 2.0f, 6.0f}; // Camera position
  
  _camera.target = {-1.f, -21.f, -34.f};   // Camera looking at point
  _camera.up = (Vector3){0.0f, 1.0f, 0.0f}; // Camera up vector (rotation towards target)
  _camera.fovy = 60.0f;                             // Camera field-of-view Y
  _camera.projection = CAMERA_PERSPECTIVE;
  _slin = 1.0f;
  _sang = 3.0f;
}

void CameraHandler::setup(Shared& state)
{
  // getCamera returs a reference, we want a ptr
  state.camera = &this->_camera;
  state.camera_view = &this->_camera_view;
}

void CameraHandler::whichView(Shared& state)
{
  if(state.is->kbd_c) 
  {
    _camera_view = CAMERA;
  }
  else if(state.is->kbd_v) 
  {
    _camera_view = CAMERA_LOCK;
  }
  else if (state.is->kbd_b)
  {
    _camera_view = PLAYER;
  }
  else 
  {
    //_camera_view = _camera_view;
  }
}

void CameraHandler::process(Shared &state)
{
  whichView(state);

  if(_camera_view == CAMERA_LOCK)
  {
    return;
  }
  else if (_camera_view == CAMERA) 
  {
    // Coodinates in local camera frame
    float dx, dy, dz;
    float dpsi, dtheta, dphi;

    dx = state.is->lin_x * _slin;
    dy = state.is->lin_y * _slin;
    dz = state.is->lin_z * _slin;

    dpsi = state.is->rot_x * _sang;
    dtheta = state.is->rot_y * _sang;
    dphi = state.is->rot_z * _sang;

    UpdateCameraPro(&_camera, (Vector3){dx, dy, dz},
                    (Vector3){dpsi, dtheta, dphi},
                     state.is->mou_s* 2.0f); // Move to target (zoom)
  }

  else if (_camera_view == PLAYER) {
    float x, y, z;
    x = state.selected_object_pose.wf_translation.x;
    y = state.selected_object_pose.wf_translation.y - _cposoff_y;
    z = state.selected_object_pose.wf_translation.z - _cposoff_z;

    _camera.position = Vector3{x, y, z};
    _camera.target = state.selected_object_pose.wf_translation;
  }
} // process

const Camera &CameraHandler::getCamera() { return _camera; }