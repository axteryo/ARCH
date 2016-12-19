#ifndef ARCHGAME_H
#define ARCHGAME_H


#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <string>
#include <math.h>
#include <iostream>

#include "unMoveableBody.h"
#include "MoveableBody.h"

#include "AnimatableGraphic.h"
#include "wallObject.h"
#include "Player.h"
#include "Actor.h"
#include "GameObject.h"
#include "includes.h"




#include <chrono>


#include "gameController.h"
#include "cam.h"
#include "LevelManager.h"


class ArchGame
{
    private:

        /**Game State Variables **/
        enum state
        {
            In_Game,
            Main_Menu,
        }GameState;

        bool gameRunning;

        /**SFML variables**/
        sf::Vector2f v2f_windowSize;
        sf::RenderWindow* window;
        sf::Keyboard keyboard;
        sf::Mouse mouse;
        sf::Vector2f v2f_mousePos;
        sf::Event event;
        sf::Keyboard input;
        sf::Clock clock;
        sf::Time accumulator;
        sf::Time ups;
        float td;
        sf::Vector2f targ;

        cam* dynamicCam;
        std::string subject;

        float32 timeStep;
        int32 velocityIterations;
        int32 positionIterations;


        LevelManager level;
        gameController controller;
        Player* p;
        bool playerAlive;

    public:



        ArchGame();

        void start();

        void processInput(state currentState);

        void update(state currentState);

        void render(state currentState);

        sf::Texture t;
        wallObject* w;


    protected:

};

#endif // ARCHGAME_H
