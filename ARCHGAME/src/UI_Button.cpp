#include "UI_Button.h"

UI_Button::UI_Button(std::string i)
{
    id = i;
    ui_type = BUTTON;
    control_press_state=CONTROL_PRESS_F;
    control_over_state =CONTROL_OVER_F;
}

UI_Button::~UI_Button()
{

}

void UI_Button::onControlOver()
{
    control_over_state = CONTROL_OVER_T;
}
void UI_Button::onControlOverNot()
{
    control_over_state = CONTROL_OVER_F;
}
void UI_Button::onControlPress()
{
    control_press_state = CONTROL_PRESS_T;
}
void UI_Button::onControlRelease()
{
    control_press_state = CONTROL_PRESS_F;
}

void UI_Button::update()
{
     switch(control_over_state)
        {
        case CONTROL_OVER_T:
            rectbody.setOutlineColor(sf::Color::Red);
            texture_coordinates = onControlOver_texture_coordinates;
            break;
        case CONTROL_OVER_F:
            rectbody.setOutlineColor(sf::Color::Blue);
            texture_coordinates = default_texture_coordinates;
            break;
        }
        switch(control_press_state)
        {
        case CONTROL_PRESS_T:
            rectbody.setFillColor(sf::Color::Blue);
            break;
        case CONTROL_PRESS_F:
            rectbody.setFillColor(sf::Color::Transparent);
            break;
        }

}
