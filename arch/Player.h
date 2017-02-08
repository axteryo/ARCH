#ifndef PLAYER_H
#define PLAYER_H

#include "Actor.h"
#include "MoveableBody.h"
#include "AnimatableGraphic.h"
#include <iostream>
#include "RadiusBody.h"
#include "includes.h"


class Player: public Actor
{
    public:
        Player(MoveableBody* p, AnimatableGraphic* g);
        virtual ~Player();

        void update();
        void setPosition(float x, float y);
        b2Vec2 getPosition();
        void setRotation(float angle);
        sf::Sprite getSprite();

        //
        void handleCollision(GameObject* obj,std::string fixtureType,std::string self_fixtureType);
        void initiateCollision(GameObject* obj,std::string fixtureType,std::string self_fixtureType);
        void resolveCollision(GameObject* obj,std::string fixtureType,std::string self_fixtureType);

        ///State setting functions
        void activateThrusters();
        void cancelThrusters();
        void cancelRightTurn();
        void cancelLeftTurn();



        void setTurnRight();
        void setTurnLeft();
        void setNoAttack();



        bool isAlive();
        bool isImpacted();
        void gaugeAttack(std::string attack,b2Vec2 direction);
        void useAttack(int a);
        void setDamageAmount(int a);
        void takeDamage();

        ///Action Functions
        void turnRight();
        void turnLeft();
        void thrust();
        void arrive();
        void laser();
        //void handleInput(sf::Keyboard k);

        float turnRate;
        float thrustLevel;

        bool thrusting;
        bool rRotate;
        bool lRotate;
        bool firing;

        int attackDuration;
        int attackCoolDown;



        enum ThrustingState
        {
            THRUST_T,
            THRUST_F
        }thrustState;

        enum TurningRightState
        {

            TURN_RIGHT,
            TURN_RIGHT_F
        }turnRightState;
          enum TurningLeftState
        {
            TURN_LEFT,
            TURN_LEFT_F
        }turnLeftState;

       // std::stack<TurningState> turnStack;

        enum AttackState
        {
            LASER,
            NO_ATTACK
        }attackTypeState;

    b2Fixture* attackFixture;



    protected:
    private:
};

#endif // PLAYER_H
