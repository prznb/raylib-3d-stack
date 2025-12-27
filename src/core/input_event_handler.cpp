#include "input_event_handler.hpp"
#include "raylib.h"

void InputEventHandler::setup(Shared &state)
{
    state.is = &_is;
}

void InputEventHandler::process(Shared &state) 
{
    capture();
}

void InputEventHandler::capture() 
{
  _is.lin_x = (IsKeyDown(KEY_W) - IsKeyDown(KEY_S));
  _is.lin_y = (IsKeyDown(KEY_D) - IsKeyDown(KEY_A));
  _is.lin_z = (IsKeyDown(KEY_LEFT_SHIFT) - IsKeyDown(KEY_LEFT_CONTROL));
  _is.rot_x = (IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT) + GetMouseDelta().x);
  _is.rot_y = (IsKeyDown(KEY_DOWN) - IsKeyDown(KEY_UP) + GetMouseDelta().y);
  _is.rot_z = (IsKeyDown(KEY_E) - IsKeyDown(KEY_Q));

  _is.kbd_c = IsKeyDown(KEY_C);
  _is.kbd_v = IsKeyDown(KEY_V);
  _is.kbd_b = IsKeyDown(KEY_B);
  _is.kbd_space = IsKeyDown(KEY_SPACE);

  _is.mou_s = GetMouseWheelMove();
}