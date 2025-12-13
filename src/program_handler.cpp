#include "program_handler.hpp"
#include "raylib.h"


ProgramHandler::ProgramHandler() : _w(1000, 600, "Debug"), 
                                   _m(_ss,_r,_dw)
{
  _w.SetTargetFPS(60);
  _target = LoadRenderTexture(1000, 600);
  _shader = LoadShader("vendor/raylib/examples/shaders/resources/shaders/glsl330/fisheye.vs", "vendor/raylib/examples/shaders/resources/shaders/glsl330/fisheye.fs");
}

void ProgramHandler::run() 
{  
  _m.loadTestNRandomCubesAndSpheres(100);

  while (!_w.ShouldClose()) // Detect window close button or ESC key
  {
    process();
    draw();
  }
}

void ProgramHandler::draw()
{ 
  BeginTextureMode(_target); 
    ClearBackground(RAYWHITE); 
    BeginMode3D(_cc.getCamera());
      _r.display(_ss);
    EndMode3D();
  EndTextureMode();
  
  BeginDrawing();
  ClearBackground(RAYWHITE); 

  BeginShaderMode(_shader);
    DrawTextureRec(_target.texture, (Rectangle){ 0, 0, (float)_target.texture.width, (float)-_target.texture.height }, (Vector2){ 0, 0 }, WHITE);
  EndShaderMode();

  _gh.display(_ss);
  EndDrawing();
}

void ProgramHandler::process()
{
  // Process program logic on the respective subsystems 
  _ieh.process(_ss); // Input events
  _s.process(_ss);   // Physics shaper
  _dw.process(_ss, _s.passover());  // Physics world
  _r.process(_ss, _dw.passover());   // Renderer/Object
  _cc.process(_ss);  // Camera
  _gh.process(_ss);  // Gui overlay
}