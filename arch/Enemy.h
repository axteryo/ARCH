#ifndef ENEMY_H
#define ENEMY_H

#include "Actor.h"
#include "MoveableBody.h"
#include "AnimatableGraphic.h"
#include "includes.h"



class Enemy : public Actor
{
    public:
        Enemy();
        virtual ~Enemy();
        /// Base Actor functions
        virtual void update() = 0;
        virtual void setPosition(float x, float y)= 0;
        virtual void setRotation(float angle)= 0;
        virtual sf::Sprite getSprite()= 0;
        ///Base enemy functions
        virtual void goToward(float x, float y)= 0;
        virtual void target(float x, float y)=0;
        virtual void setInactive() = 0;

        MoveableBody* _physicsBody;
        AnimatableGraphic* _graphicsBody;

        ///Base Enemy States
        enum basicState
        {
            neutral,
            offense,
            defensive

        }baseState;
        enum secondaryState
        {
            ///Offense_substate
            chase,
            attacking,
            ///Neutral_substate
            alerted,
            unalerted,
            inactive
        }secondState;
    protected:
    private:
};

#endif // ENEMY_H
