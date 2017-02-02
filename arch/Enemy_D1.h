#ifndef ENEMY_D1_H
#define ENEMY_D1_H

#include "Enemy.h"
#include <iostream>

class Enemy_D1: public Enemy
{
    public:
        Enemy_D1(MoveableBody* p, AnimatableGraphic* g);
        virtual ~Enemy_D1();
        /// Base Actor functions
        void update();
        void setPosition(float x, float y);
        b2Vec2 getPosition();
        void setRotation(float angle);
        sf::Sprite getSprite();
        void handleCollision(GameObject* obj,std::string fixtureType,std::string self_fixtureType);
        ///Base enemy functions
        void goToward(float x, float y);
        void target(float x, float y);
        void setInactive();
        void setTarget(GameObject* gObj);
        void setNeutral();
        void setOffense();
        void setDefensive();
        void setUnalerted();
        void setAlerted();
        void setChase();
        void setAttacking();
        void gaugeAttack(std::string attack,b2Vec2 direction);

        int impactDuration;
    protected:
    private:
};

#endif // ENEMY_D1_H
