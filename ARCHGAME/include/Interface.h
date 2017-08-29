#ifndef INTERFACE_H
#define INTERFACE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include "UI_Button.h"
#include "UI_Panel.h"
#include "GameController.h"
#include "GameEvent_Interface.h"
#include "GameEventListener.h"



class Interface
{
    public:
        Interface(std::string i,GameEventListener* e);
        virtual ~Interface();
        //void run(GameState* gameState);
        void processWindowEvents(sf::Event e);
        void setup(sf::View v);
        void setMainPanel(UI_Panel* p);
        void addButton(UI_Button* b);
        void activateButton(UI_Button* b);
        void activate();
        void deactivate();
        void selectForward();
        void selectBackward();
        void select();
        void unselect();
        void update(GameController& controller);
        void draw(sf::RenderWindow* w);
        std::string getID();
        bool isActive();
        UI_Panel* mainPanel;
        std::vector<UI_Button*> buttonList;
    protected:
    private:
    bool active;
    std::string id;
    sf::Vector2f position;
    int currentButton;

    UI_Button* activeButton;
    GameEventListener* _listener;
};

#endif // INTERFACE_H
