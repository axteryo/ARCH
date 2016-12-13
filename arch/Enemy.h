#ifndef ENEMY_H
#define ENEMY_H

#include "Actor.h"
#include "MoveableBody.h"
#include "AnimatableGraphic.h"
#include "includes.h"



class Enemy : public Actor
{
    public:
        Enemy(MoveableBody* p, AnimatableGraphic* g);
        virtual ~Enemy();

        void setPosition(float x, float y);
        void update();
        void goToward(float x, float y);
        void lookAt(float x, float y);
        sf::Sprite getSprite();

        MoveableBody* _physicsBody;
        AnimatableGraphic* _graphicsBody;


        enum baseState
        {
            neutral,
            chase,
            offense,
            defensive,
            alerted
        }bState;
    protected:
    private:
};

#endif // ENEMY_H
