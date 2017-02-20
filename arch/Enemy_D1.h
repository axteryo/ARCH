#ifndef ENEMY_D1_H
#define ENEMY_D1_H

#include "Enemy.h"
#include "Subject.h"
#include <iostream>

class Enemy_D1 : public Enemy//, public Subject
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
        void arrive();
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
        void drain();

        void initiateCollision(GameObject* obj,std::string fixtureType,std::string self_fixtureType);
        void resolveCollision(GameObject* obj,std::string fixtureType,std::string self_fixtureType);

        bool isAlive();
        bool isImpacted();
        void gaugeAttack(std::string attack,b2Vec2 direction);
        void useAttack(int a);
        void setNoAttack();
        void setDamageAmount(int a);
        void takeDamage();

        float getDistanceFromTarget(b2Vec2 t);

        int attackDuration;
        int attackCoolDown;
        b2Fixture* attackFixture;


        ///D1s BehaviorStack
        std::stack<secondaryState> actionStack;
         enum AttackState
        {
            DRAIN,
            NO_ATTACK
        }attackTypeState;




    protected:
    private:
};

#endif // ENEMY_D1_H
