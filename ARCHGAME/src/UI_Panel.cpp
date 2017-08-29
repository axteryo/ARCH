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

void UI_Panel::arrangeElementsHorizontally()
{
    int j = childElementsList.size();
    for(int i = 0;i<childElementsList.size();i++)
    {
        sf::Vector2f pos;
        pos.x = position.x+dimensions.x/2;
        if(i<1)
        {
        pos.y = (position.y)+((dimensions.y)/(j+1));
        }
        else
        {
            pos.y = childElementsList[i-1]->getPosition().y;
            pos.y+=(dimensions.y/(j+(j/2)));
        }

        childElementsList[i]->setPosition(pos);
        //j--;
    }
}
void UI_Panel::addChildElement(UI_Element* c)
{
    childElementsList.push_back(c);
}
