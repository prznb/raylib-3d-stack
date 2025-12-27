#pragma once
#include "raylib.h"
#include "shared_state.hpp"
#include <nlohmann/json.hpp>


using json = nlohmann::json;

class InputEventHandler 
{
  json map;
public:
  InputEventHandler();

  void process(Shared &state);
  void capture();
};
