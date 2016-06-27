#ifndef ACTOR_H
#define ACTOR_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <math.h>


class Actor
{
    public:
        Actor();

        //void goToward(sf::Vector2f dir);

        void jump();

        //void checkCol();

        void update();

        void setLocation(float lX,float lY);

        sf::Sprite getSprite();

        bool checkGrounded();

        void setStationary();
        void setRight();
        void setLeft();
        //void setJump();


    protected:
    private:
        /** sprite properties**/
        sf::Texture wizTexture;
        sf::Sprite sprite;
        enum actorState
        {
            ac_Stationary,
            ac_Right,
            ac_Left,
            ac_Jump

        }actState;
        //sf::Vector2f location;
        //sf::Vector2f velocity;
        //sf::Vector2f acceleration;

        /** Physics properties**/
        //body definition
        b2BodyDef bodyDef;

        //shape definition
        b2PolygonShape polyShape;

        //Dynamic body
        b2Body* body;

        //Fixture
        b2FixtureDef fixtureDef;

        float remainingJumpSteps;
        float desiredVertVel;


};

#endif // ACTOR_H
