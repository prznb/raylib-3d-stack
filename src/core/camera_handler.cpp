#include "camera_handler.hpp"

CameraHandler::CameraHandler() {
  _camera.position = (Vector3){0.0f, 2.0f, 100.0f}; // Camera position
  _camera.target = (Vector3){0.0f, 2.0f, 0.0f};   // Camera looking at point
  _camera.up =
      (Vector3){0.0f, 1.0f, 0.0f}; // Camera up vector (rotation towards target)
  _camera.fovy = 60.0f;            // Camera field-of-view Y
  _camera.projection = CAMERA_PERSPECTIVE;

  _slin = 1.0f;
  _sang = 3.0f;
}

void CameraHandler::process(Shared &state) {
  if (state.io == CAMERA) {
    // Coodinates in local camera frame
    float dx, dy, dz;
    float dpsi, dtheta, dphi;

    dx = (IsKeyDown(KEY_W) - IsKeyDown(KEY_S)) * _slin;
    dy = (IsKeyDown(KEY_D) - IsKeyDown(KEY_A)) * _slin;
    dz = (IsKeyDown(KEY_LEFT_SHIFT) - IsKeyDown(KEY_LEFT_CONTROL)) * _slin;

    dpsi = (IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT) + GetMouseDelta().x) *
           _sang;
    dtheta =
        (IsKeyDown(KEY_DOWN) - IsKeyDown(KEY_UP) + GetMouseDelta().y) * _sang;
    dphi = (IsKeyDown(KEY_E) - IsKeyDown(KEY_Q)) * _sang;

    UpdateCameraPro(&_camera, (Vector3){dx, dy, dz},
                    (Vector3){dpsi, dtheta, dphi},
                    GetMouseWheelMove() * 2.0f); // Move to target (zoom)
  }

  else if (state.io == PLAYER || state.io == SHAPER) {
    // World frame coordinates
    float x, y, z;

    x = state.selected_object_pose.wf_translation.x;
    y = state.selected_object_pose.wf_translation.y - _cposoff_y; // - test_offset;
    z = state.selected_object_pose.wf_translation.z - _cposoff_z;

    _camera.position = Vector3{x, y, z};
    _camera.target = state.selected_object_pose.wf_translation;
    // _camera.up ??
  }
} // process

const Camera &CameraHandler::getCamera() { return _camera; }