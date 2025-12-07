#include "input_event_handler.hpp"

void InputEventHandler::process(Shared &state) {
  // Evaluate Input Processing Ownership
  if (IsKeyDown(KEY_C)) {
    state.io = CAMERA;
  }
  if (IsKeyDown(KEY_V)) {
    state.io = PLAYER;
  }
  if (IsKeyDown(KEY_B)) {
    state.io = SHAPER;
  }
}
