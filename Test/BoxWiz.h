#ifndef BOXWIZ_H
#define BOXWIZ_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <math.h>

#include "BoxWiz.h"
#include "dist/json/json.h"
#include "dist/json/json-forwards.h"

extern b2Vec2 gravity;
extern b2World world;

class BoxWiz
{
    private:
        enum state
        {
            In_Game,
            Main_Menu,
        } GameState;

        bool gameRunning;

        sf::Vector2f windowDim;
        sf::RenderWindow* window;
        sf::Keyboard keyboard;
        sf::Mouse mouse;
        sf::Vector2f mousePos;
        sf::Event event;

        /** box2d world variables**/
        b2Vec2 gravity;

        float32 timeStep;
        int32 velocityIterations;
        int32 positionIterations;


    public:
        BoxWiz();

        void start(state currentState);

        void processInput(state currentState);

        void update(state currentState);

        void render(state currentState);

        int main();
    protected:

};

#endif // BOXWIZ_H
