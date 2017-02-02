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
        virtual b2Vec2 getPosition()= 0;
        virtual void setRotation(float angle)= 0;
        virtual sf::Sprite getSprite()= 0;
        //virtual void handleCollision(std::string objId,std::string fixtureType,std::string self_fixtureType) = 0;
        ///Base enemy functions
        virtual void goToward(float x, float y)= 0;
        virtual void target(float x, float y)=0;
        virtual void setInactive() = 0;
        virtual void setTarget(GameObject* gObj) = 0;
        virtual void setNeutral()= 0;
        virtual void setOffense() = 0;
        virtual void setDefensive() = 0;
        virtual void setUnalerted() = 0;
        virtual void setAlerted()= 0;
        virtual void setChase() = 0;
        virtual void setAttacking() = 0;


        std::stack<GameObject*> targetStack;

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
