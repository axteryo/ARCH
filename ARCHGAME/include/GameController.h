#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H


#include "json/json.h"
#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Window.hpp>



class GameController
{
    public:
        GameController();
        virtual ~GameController();
        void loadBindings();
        void setBindings();
        bool isActionKeyPressed(std::string actionToCheck);
        bool isBindedKeyPressed(std::string bindingToCheck);
    protected:
    private:
        sf::Keyboard keyBoard;
        //sf::Joystick joyStick;
        std::string playerThrustAction;
        std::string playerTurnLeftAction;
        std::string playerTurnRightAction;
        std::string playerUseAttack1Action;
        std::string playerBrakeAction;
        enum controllerTypeState
        {
            KEYBOARD_MOUSE,
            JOYSTICK
        }controllerState;
};

#endif // GAMECONTROLLER_H
