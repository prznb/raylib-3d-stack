#include "shared_state.hpp"
#include <utility>
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
              "Camera Params");
  
  cursor_y += cursor_y_increment;
  cursor_x += cursor_x_increment;

  DrawText(TextFormat("Position: X = %0.f, Y = %0.f, Z = %0.f",
                      state.camera->position.x,
                      state.camera->position.y,
                      state.camera->position.z),
           cursor_x, cursor_y, TXT_SIZE, DARKBLUE);

  cursor_y += cursor_y_increment;

    DrawText(TextFormat("Target: X = %0.f, Y = %0.f, Z = %0.f",
                      state.camera->target.x,
                      state.camera->target.y,
                      state.camera->target.z),
           cursor_x, cursor_y, TXT_SIZE, DARKBLUE);
  
  // New panel - Vehicle tuning
  cursor_y =
      _bottom_panel_height +
      UPPER_LIM_Y; // defines current position of the panel item to draw (ROW)
 
  cursor_x += _bottom_panel_item_width;
  
  GuiGroupBox((Rectangle){cursor_x, cursor_y, _bottom_panel_item_width,
                          _offset_panel_height - LOWER_LIM_Y},"Vehicle Params");
  
  // get info from one wheel then assign to the other ones
  btWheelInfo &wheel= state.vehicle->getWheelInfo(0);

  float suspensionStiffness       = wheel.m_suspensionStiffness;
  float wheelsDampingRelaxation   = wheel.m_wheelsDampingRelaxation;      
  float wheelsDampingCompression  = wheel.m_wheelsDampingCompression;    
  float frictionSlip              = wheel.m_frictionSlip;
  float rollInfluence             = wheel.m_rollInfluence; 
  float maxSuspensionTravelCm     = wheel.m_maxSuspensionTravelCm;


  cursor_y += cursor_y_increment;
  cursor_x += cursor_x_increment;

  DrawText(TextFormat("Suspension Stiffness: %0.2f", suspensionStiffness),
           cursor_x, cursor_y, TXT_SIZE, DARKGREEN);
  cursor_y += 0.5*cursor_y_increment;
  Rectangle bounds = {cursor_x, cursor_y, _bottom_panel_item_width*0.7f, cursor_y_increment};
  const char* min = "0";
  const char* max = "50";
  GuiSlider(bounds,min, max, &suspensionStiffness , 0.f, 50.f);
  

  max = "500";
  // Damping relaxation
  cursor_y += cursor_y_increment;
  DrawText(TextFormat("Damping Relaxation: %0.2f", wheelsDampingRelaxation),
           cursor_x, cursor_y, TXT_SIZE, DARKGREEN);
  cursor_y += 0.5*cursor_y_increment;
  bounds = {cursor_x, cursor_y, _bottom_panel_item_width*0.7f, cursor_y_increment};
  GuiSlider(bounds,min, max, &wheelsDampingRelaxation , 0.f, 500.f);
  
  // Damping compression
  cursor_y += cursor_y_increment;
  DrawText(TextFormat("Damping Compression: %0.2f", wheelsDampingCompression),
           cursor_x, cursor_y, TXT_SIZE, DARKGREEN);
  cursor_y += 0.5*cursor_y_increment;
  bounds = {cursor_x, cursor_y, _bottom_panel_item_width*0.7f, cursor_y_increment};
  GuiSlider(bounds,min, max, &wheelsDampingCompression , 0.f, 500.f);
  
  // Friction slip
  cursor_y += cursor_y_increment;
  DrawText(TextFormat("Friction Slip: %0.2f", frictionSlip),
           cursor_x, cursor_y, TXT_SIZE, DARKGREEN);
  cursor_y += 0.5*cursor_y_increment;
  bounds = {cursor_x, cursor_y, _bottom_panel_item_width*0.7f, cursor_y_increment};
  min = "0";
  max = "500";
  GuiSlider(bounds,min, max, &frictionSlip , 0.f, 500.f);
  
  // Suspension Force
  cursor_y += cursor_y_increment;
  DrawText(TextFormat("Suspension Travel Max (cm): %0.2f", maxSuspensionTravelCm),
           cursor_x, cursor_y, TXT_SIZE, DARKGREEN);
  cursor_y += 0.5*cursor_y_increment;
  bounds = {cursor_x, cursor_y, _bottom_panel_item_width*0.7f, cursor_y_increment};
  min = "0";
  max = "50";
  GuiSlider(bounds,min, max, &maxSuspensionTravelCm , 0.f, 50);
  
  
  // update tuning
  for (int i = 0; i < state.vehicle->getNumWheels(); i++) {
    btWheelInfo &wheel = state.vehicle->getWheelInfo(i);
    wheel.m_suspensionStiffness = suspensionStiffness;
    wheel.m_wheelsDampingRelaxation = wheelsDampingRelaxation;
    wheel.m_wheelsDampingCompression = wheelsDampingCompression;
    wheel.m_frictionSlip = frictionSlip;
    wheel.m_rollInfluence = rollInfluence;
    wheel.m_maxSuspensionTravelCm = maxSuspensionTravelCm;
  }


}
