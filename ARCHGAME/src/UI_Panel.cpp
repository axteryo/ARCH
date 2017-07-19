#include "UI_Panel.h"

UI_Panel::UI_Panel(std::string i)
{
    id = i;
    ui_type = PANEL;
    control_press_state=CONTROL_PRESS_F;
    control_over_state =CONTROL_OVER_F;
}

UI_Panel::~UI_Panel()
{
    //dtor
}
