#include "shared_state.hpp"
#define RAYGUI_IMPLEMENTATION
#define GUI_WINDOW_FILE_DIALOG_IMPLEMENTATION
#include "third-party/gui_window_file_dialog.h"
#include "third-party/raygui.h"
#include "gui_handler.hpp"
#include "raylib.h"


void gui::Handler::process(SharedState &state) {}

void gui::Handler::display(SharedState &state) {
  if (state.debug) {
    // Built-in
    DrawFPS(0, 0);

    // Draw canvas
    _bottom_panel_height = GetScreenHeight() - _offset_panel_height;
    DrawLine(0, _bottom_panel_height, GetScreenWidth(), _bottom_panel_height,
             GRAY);
    DrawRectangle(0, _bottom_panel_height, GetScreenWidth(),
                  _bottom_panel_height, Fade(RAYWHITE, 0.6f));

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
                        state.current_player_pose.translation.x,
                        state.current_player_pose.translation.y,
                        state.current_player_pose.translation.y),
             cursor_x, cursor_y, TXT_SIZE, DARKBLUE);

    cursor_y += cursor_y_increment;

    DrawText(TextFormat("Applied Forces: X = %0.f, Y = %0.f, Z = %0.f",
                        state.player_force_input.getX(),
                        state.player_force_input.getY(),
                        state.player_force_input.getZ()),
             cursor_x, cursor_y, TXT_SIZE, BLUE);

    cursor_y += cursor_y_increment;
    DrawText(TextFormat("Rotation: OX = %0.2f, OY = %0.2f, OZ = %0.2f",
                        state.getCurrentPlayerRotationEuler().x,
                        state.getCurrentPlayerRotationEuler().y,
                        state.getCurrentPlayerRotationEuler().z),
             cursor_x, cursor_y, TXT_SIZE, RED);

    cursor_y += cursor_y_increment;
    DrawText(TextFormat("Applied Torque: OX = %0.2f, OY = %0.2f, OZ = %0.2f",
                        state.player_torque_input.getX(),
                        state.player_torque_input.getY(),
                        state.player_torque_input.getZ()),
             cursor_x, cursor_y, TXT_SIZE, RED);
  }
}
