#ifndef PLAYER_H
#define PLAYER_H

#include "Actor.h"
#include "MoveableBody.h"
#include "AnimatableGraphic.h"
#include <iostream>
#include "includes.h"


class Player: public Actor
{
    public:
        Player(MoveableBody* p, AnimatableGraphic* g);
        virtual ~Player();

        void update();
        void setPosition(float x, float y);
        void setRotation(float angle);
        sf::Sprite getSprite();

        void activateThrusters();
        void cancelThrusters();
        void cancelRightTurn();
        void cancelLeftTurn();
        void turnRight();
        void turnLeft();

        void turn();
        void thrust();
        //void handleInput(sf::Keyboard k);

        float turnRate;
        float thrustLevel;

        bool thrusting;
        bool rRotate;
        bool lRotate;

        MoveableBody* _physicsBody;
        AnimatableGraphic* _graphicsBody;


    protected:
    private:
};

#endif // PLAYER_H
