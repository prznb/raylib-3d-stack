#include "shared_state.hpp"
#define RAYGUI_IMPLEMENTATION
#define GUI_WINDOW_FILE_DIALOG_IMPLEMENTATION
#include "gui_handler.hpp"
#include "raylib.h"
#include "../modules/third-party/gui_window_file_dialog.h"
#include "../modules/third-party/raygui.h"

void gui::Handler::process(Shared &state) {}

void gui::Handler::display(Shared &state) {
  if (!state.debug) {
    return;
  }
  // Built-in
  DrawFPS(0, 0);

  // Draw canvas
  /*
  _bottom_panel_height = GetScreenHeight() - _offset_panel_height;
  DrawLine(0, _bottom_panel_height, GetScreenWidth(), _bottom_panel_height,
           GRAY);
  DrawRectangle(0, _bottom_panel_height, GetScreenWidth(), _bottom_panel_height,
                Fade(RAYWHITE, 0.6f));

  // drawing variables
  const float TXT_SIZE = 10;
  // positioning variables
  const float UPPER_LIM_Y = 10;  // from the panel top
  const float LOWER_LIM_Y = -10; // from the screen border

  float cursor_x =
      0; // defines current position of the panel item to draw (COLUMN)
  float cursor_y =
      _bottom_panel_height +
      UPPER_LIM_Y; // defines current position of the panel item to draw (ROW)
  float cursor_x_increment = 20;
  float cursor_y_increment = 20;

  // Draw - Actor parameters

  GuiGroupBox((Rectangle){cursor_x, cursor_y, _bottom_panel_item_width,
                          _offset_panel_height - LOWER_LIM_Y},
              "Actor Params");
  
  cursor_y += cursor_y_increment;
  cursor_x += cursor_x_increment;

  DrawText(TextFormat("Position: X = %0.f, Y = %0.f, Z = %0.f",
                      state.selected_object_pose.wf_translation.x,
                      state.selected_object_pose.wf_translation.y,
                      state.selected_object_pose.wf_translation.y),
           cursor_x, cursor_y, TXT_SIZE, DARKBLUE);

  cursor_y += cursor_y_increment;

  
  DrawText(TextFormat("Applied Forces: X = %0.f, Y = %0.f, Z = %0.f",
                      state.external_object_forces.getX(),
                      state.external_object_forces.getY(),
                      state.external_object_forces.getZ()),
           cursor_x, cursor_y, TXT_SIZE, BLUE);

  cursor_y += cursor_y_increment;
  DrawText(TextFormat("Rotation: OX = %0.2f, OY = %0.2f, OZ = %0.2f",
                      state.getCurrentPlayerRotationEuler().x,
                      state.getCurrentPlayerRotationEuler().y,
                      state.getCurrentPlayerRotationEuler().z),
           cursor_x, cursor_y, TXT_SIZE, RED);

  cursor_y += cursor_y_increment;
  DrawText(TextFormat("Applied Torque: OX = %0.2f, OY = %0.2f, OZ = %0.2f",
                      state.external_object_torques.getX(),
                      state.external_object_torques.getY(),
                      state.external_object_torques.getZ()),
           cursor_x, cursor_y, TXT_SIZE, RED);
  */
}
