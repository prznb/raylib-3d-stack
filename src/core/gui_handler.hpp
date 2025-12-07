#pragma once

#include "shared_state.hpp"

namespace gui {
class Handler {
  float _offset_panel_height = 200;
  float _bottom_panel_height; 
  float _bottom_panel_item_width = 300;

  Vector3 _current_player_orientation = {0.f, 0.f, 0.f};

public:
  void process(SharedState &state);

  void display(SharedState &state);
};
} // namespace gui