#ifndef PLAYER_H
#define PLAYER_H

#include "Actor.h"
#include "MoveableBody.h"
#include "AnimatableGraphic.h"
#include "includes.h"


class Player: public Actor
{
    public:
        Player(MoveableBody* p, AnimatableGraphic* g);
        virtual ~Player();

        void update();
        void setPosition(float x, float y);
        void activateThrusters();
        void cancelThrusters();
        void cancelRightTurn();
        void cancelLeftTurn();
        void turnRight();
        void turnLeft();
        //void handleInput(sf::Keyboard k);
        sf::Sprite getSprite();
        float turnRate;
        float thrustLevel;

        bool thrust;
        bool rRotate;
        bool lRotate;

        MoveableBody* _physicsBody;
        AnimatableGraphic* _graphicsBody;


    protected:
    private:
};

#endif // PLAYER_H
