#ifndef ARCHGAME_H
#define ARCHGAME_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <math.h>
#include "GameObject.h"

extern b2Vec2 gravity;
extern b2World* world;
extern std::vector<GameObject> objectList;

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

        float32 timeStep;
        int32 velocityIterations;
        int32 positionIterations;




    public:



        ArchGame();

        void start();

        void processInput(state currentState);

        void update(state currentState);

        void render(state currentState);


    protected:

};

#endif // ARCHGAME_H
