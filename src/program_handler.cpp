#include "program_handler.hpp"
#include "modules/shared_state.hpp"
#include "raylib.h"

ProgramHandler::ProgramHandler() : _window_handler(1000, 600, "Debug")
{
  _window_handler.SetTargetFPS(60);
}

void ProgramHandler::run() 
{  
  _bullet_physics.setup(_state);
  _renderer_scene.setup(_state);
  _state.verify();

  while (!_window_handler.ShouldClose()) // Detect window close button or ESC key
  {
    // Process program logic on the respective subsystems 
    _input_events.process(_state); // Input events
    _bullet_physics_ext_interface.process(_state);   // Physics shaper
    _bullet_physics.process(_state);  // Physics world
    _renderer_scene.process(_state);   // Renderer/Object
    _camera_handler.process(_state);  // Camera
    _gui.process(_state);  // Gui overlay

    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(_camera_handler.getCamera());
    _renderer_scene.display(_state);
    EndMode3D();
    _gui.display(_state);
    EndDrawing();
  }
}
