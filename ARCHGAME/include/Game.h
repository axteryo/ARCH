#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>

#include <string>
#include <math.h>
#include <iostream>


#include "level.h"
#include "GameController.h"
#include "camera.h"
#include "AudioSystem.h"


extern AudioSystem* audioSystem;

class Game
{
    public:
        Game();
        virtual ~Game();
        void start();
        void _end();
    protected:
    private:
        /**Game Variables**/

        bool gameRunning;

        /**SFML Variables**/
        sf::Vector2f v2f_windowSize;
        sf::RenderWindow* window;
        sf::Keyboard keyBoard;
        sf::Mouse mouse;
        sf::Vector2f v2f_mousePos;
        sf::Event event;
        sf::Clock clock;

        sf::View tempView;

        sf::Time currentTime;
        double flPreviousTime;
        double dt;

        /**Box2d Variables**/

        double timeStep;
        int32 velocityIterations;
        int32 positionIterations;
        bool isVsynced;




        void processInput();
        void update(float dt);
        void render(double alpha);

        level gameLevel;
        //GameController controller;



};

#endif // GAME_H
