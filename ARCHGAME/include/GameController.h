#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H


//#include "json/json.h"
//#include <iostream>
//#include <fstream>
#include "JsonHandler.h"
#include <string>
#include <SFML/Window.hpp>



class GameController
{
    public:
        GameController();
        virtual ~GameController();
        void loadDefaultBindings();
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
        std::string playerBoostAction;
        std::string playerUseAttack1Action;
        std::string playerUseAttack2Action;
        std::string playerUseAttack3Action;
        std::string playerBrakeAction;
        std::string selectForwardAction;
        std::string selectBackwardAction;
        std::string confirmSelectionAction;

        enum controllerTypeState
        {
            KEYBOARD_MOUSE,
            JOYSTICK
        }controllerState;

        Json::Value baseKeyRoot;
        JsonHandler jsonHandler;


};

#endif // GAMECONTROLLER_H
