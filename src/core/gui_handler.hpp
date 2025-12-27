#pragma once

#include "shared_state.hpp"
#include <vector>

namespace gui {
class Handler {
  float _offset_panel_height = 200;
  float _bottom_panel_height; 
  float _bottom_panel_item_width = 300;

public:
  void process(Shared &state);
  void display(Shared &state);
};
} // namespace gui