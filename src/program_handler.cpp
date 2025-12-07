#include "program_handler.hpp"


ProgramHandler::ProgramHandler() : _w(1000, 600, "Debug")
{
  _w.SetTargetFPS(60);
}

void ProgramHandler::run() 
{  
  _dw.setup(_ss);
  _r.setup(_ss);
  _ss.verify();

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
    EndMode3D();
    _gh.display(_ss);
    EndDrawing();
  }
}
