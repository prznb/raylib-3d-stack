#pragma once
#include "raylib.h"
#include "shared_state.hpp"
#include "types.hpp"


class CameraHandler {
public:
  CameraHandler();
  ~CameraHandler() = default;
  
  void setup(Shared& state);
  void process(Shared& state);

  const Camera &getCamera();

private:
  void whichView(Shared& state);

  Camera _camera;
  CameraMode _camera_mode;
  CameraView _camera_view = CAMERA_LOCK;

  float _slin = 0.1f;  // speed linear
  float _sang = 0.05f; // speed angular
  float _cposoff_y = -3.f;
  float _cposoff_z = 7.f;
};