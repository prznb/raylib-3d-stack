#pragma once
#include "shared_state.hpp"
#include "types.hpp"
#include <nlohmann/json.hpp>


using json = nlohmann::json;

class InputEventHandler {
  json _map;
  InputStorage _is;
  void capture();
public:
  InputEventHandler(){};
  void setup(Shared &state);
  void process(Shared &state);
};
