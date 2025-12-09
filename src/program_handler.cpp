#include "program_handler.hpp"


ProgramHandler::ProgramHandler() : _w(1000, 600, "Debug"), 
                                   _m(_ss,_r,_dw)
{
  _w.SetTargetFPS(60);
}

void ProgramHandler::run() 
{  
  //_m.loadTestNRandomCubesAndSpheres(100);
  //_m.loadTestNRandomCubes(100);
  //_m.loadTestNRandomCylinders(100);
  //_m.saveSimulation();
  _m.loadTestWorldFromSavedFile();

  while (!_w.ShouldClose()) // Detect window close button or ESC key
  {
    // Process program logic on the respective subsystems 
    _ieh.process(_ss); // Input events
    _s.process(_ss);   // Physics shaper
    _dw.process(_ss, _s.passover());  // Physics world
    _r.process(_ss, _dw.passover());   // Renderer/Object
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
