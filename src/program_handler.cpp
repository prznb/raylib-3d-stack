#include "program_handler.hpp"
#include "raylib.h"



ProgramHandler::ProgramHandler() : _w(1000, 600, "Debug"), _dw(_s, _pb) 
{
  _w.SetTargetFPS(60);
}

void ProgramHandler::run() 
{  
  _dw.setup();
  // For the tests - this is a single and the same object in two representation
  _dw.addObject();
  _r.addObject();

  while (!_w.ShouldClose()) // Detect window close button or ESC key
  {
    // Process program logic on the respective subsystems 
    _ieh.process(_ss); // Input events
    _s.process(_ss);   // Physics shaper
    _dw.process(_ss);  // Physics world
    _r.process(_ss);   // Renderer/Object
    _cc.process(_ss);  // Camera
    _gh.process(_ss);  // Gui overlay

    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(_cc.getCamera());
    _r.display(_ss);
    DrawGrid(250, 2);
    EndMode3D();
    _gh.display(_ss);
    EndDrawing();
  }
}
