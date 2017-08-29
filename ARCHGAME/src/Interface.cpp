#include "Interface.h"

Interface::Interface(std::string i,GameEventListener* e)
{
    id = i;
    activeButton = nullptr;
    mainPanel = nullptr;
    position = sf::Vector2f(0,0);
    currentButton = 0;
    _listener = e;
}

Interface::~Interface()
{
    //dtor
    delete _listener;
}
std::string Interface::getID()
{
    return id;
}
bool Interface::isActive()
{
    return active;
}
void Interface::addButton(UI_Button* b)
{
    buttonList.push_back(b);
}

void Interface::processWindowEvents(sf::Event e)
{
    if(active)
    {
         /* for(int i = 0; i <buttonList.size();i++)
        {
           //sf::Vector2i pos = mouse.getPosition(window);
            if(e.type == sf::Event::MouseMoved)
            {   //window.setMouseCursorVisible(true);
                if(buttonList[i]->isMouseOver(sf::Vector2f(pos.x,pos.y)))
                {
                    setActive(buttonList[i]);
                    currentButton = i;
                }
            }
            if((e.type == sf::Event::MouseButtonPressed) && (e.mouseButton.button == sf::Mouse::Left))
            {
                 if(buttonList[i]->isMouseOver(sf::Vector2f(pos.x,pos.y)))
                {
                    confirmSelection();
                }
                //else{unConfirmSelec
            }
            if((e.type == sf::Event::MouseButtonReleased) && (e.mouseButton.button == sf::Mouse::Left))
            {
               /* switch (control_over_state)
                {
                case CONTROL_OVER_T:
                   control_press_state = CONTROL_PRESS_F;
                    break;
                case CONTROL_OVER_F:
                     control_press_state = CONTROL_PRESS_F;
                    break;
                }
            }
        }*/

    }
}
void Interface::setup(sf::View v)
{
    activateButton(buttonList[currentButton]);
    sf::Vector2f panel_dim = mainPanel->getDimensions();
    //position = sf::Vector2f(v.getCenter().x-(panel_dim.x/2),v.getCenter().y-(panel_dim.y/2));
    mainPanel->setPosition(v.getCenter());
    for(int i = 0; i<buttonList.size();i++)
    {
        mainPanel->addChildElement(buttonList[i]);
        //buttonList[i]->setPosition(position);
    }
    mainPanel->arrangeElementsHorizontally();
}
void Interface::setMainPanel(UI_Panel* p)
{
    mainPanel = p;
}
void Interface::activateButton(UI_Button* b)
{
    if(activeButton!=nullptr)
    {
        activeButton->onControlOverNot();
        activeButton->onControlRelease();
        activeButton->update();
    }
     activeButton = b;
     activeButton->onControlOver();
}
void Interface::activate()
{
    active = true;
}
void Interface::deactivate()
{
    active = false;
}
void Interface::selectForward()
{
    //window.setMouseCursorVisible(false);
    currentButton-=1;
    if(currentButton<0)
    {
        currentButton=buttonList.size()-1;
    }
    activateButton(buttonList[currentButton]);
    GameEvent_Interface* i = new GameEvent_Interface(BUTTON_OVER,activeButton->getID());
    _listener->notifyEvent(i);
}
void Interface::selectBackward()
{
    //window.setMouseCursorVisible(false);
    currentButton++;
    if(currentButton>=buttonList.size())
    {
        currentButton = 0;
    }
    activateButton(buttonList[currentButton]);
    GameEvent_Interface* i = new GameEvent_Interface(BUTTON_OVER,activeButton->getID());
    _listener->notifyEvent(i);
}
void Interface::select()
{
    activeButton->onControlPress();
    GameEvent_Interface* i = new GameEvent_Interface(BUTTON_SELECT,activeButton->getID());
    _listener->notifyEvent(i);
}
void Interface::unselect()
{
    activeButton->onControlRelease();
}
void Interface::update(GameController& controller)
{
     if(controller.isActionKeyPressed("confirmSelection"))
    {
        select();
    }
    else{unselect();}

    if(controller.isActionKeyPressed("selectForward"))
    {
        selectForward();
    }
    if(controller.isActionKeyPressed("selectBackward"))
    {
        selectBackward();
    }
     activeButton->update();

}
void Interface::draw(sf::RenderWindow* w)
{
   /* if(mainPanel!=nullptr)
    {
        w->draw(mainPanel->getBody());
        w->draw(mainPanel->graphic.getSprite());
        for(int i = 0; i <buttonList.size(); i++)
        {
            w->draw(buttonList[i]->getGraphic().getSprite());
            w->draw(buttonList[i]->getRectBody());
        }
    }*/
}
