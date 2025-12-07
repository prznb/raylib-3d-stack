#pragma once
#include "raylib.h"
#include "shared_state.hpp"



class InputEventHandler {
public:
  InputEventHandler(){};

  void process(Shared &state);
};
