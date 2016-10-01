#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H



#include "dist/json/json.h"
#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Window.hpp>


class gameController
{
    public:
        gameController();
        virtual ~gameController();
        void loadBinding();
        void setBinding();
        bool isBindedKeyPressed(std::string bindingToCheck);
        bool isBindedKeyReleased(std::string bindingToCheck, sf::Event e);
        bool isActionKeyPressed(std::string actionToCheck);
        bool isActionKeyReleased(std::string actionToCheck, sf::Event e);

        std::string activateThrustersAction;
        std::string turnLeftAction;
        std::string turnRightAction;

    protected:
    private:
};

#endif // GAMECONTROLLER_H
