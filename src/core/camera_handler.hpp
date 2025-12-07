#pragma once
#include "raylib.h"
#include "shared_state.hpp"


class CameraHandler {
public:
  CameraHandler();
  ~CameraHandler() = default;

  void process(Shared &state);

  const Camera &getCamera();

private:
  // Methods
  // N/A

  // Member variables
  Camera _camera;
  CameraMode _camera_mode;

  float _slin = 0.1f;  // speed linear
  float _sang = 0.05f; // speed angular
  float _cposoff_y = -30.f;
  float _cposoff_z = 40.f;
};