#ifndef ACTOR_H
#define ACTOR_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "GameObject.h"
#include "includes.h"
#include "RadiusBody.h"

class MoveableBody;
class AnimatableGraphic;



class Actor:public GameObject
{
    public:
        Actor();
        virtual ~Actor();

        //virtual void update() = 0;
        //void setPosition(float x, float y);
        //virtual b2Vec2 getPosition() = 0;
        //virtual void setRotation(float angle) = 0;
        virtual sf::Sprite getSprite() = 0;


        virtual bool isAlive() = 0;
        virtual bool isImpacted() = 0;
        virtual void gaugeAttack(std::string attack,b2Vec2 direction) = 0;
        virtual void useAttack(int a) = 0;
        virtual void setNoAttack() = 0;
        virtual void setDamageAmount(int a)= 0;
        virtual void takeDamage() = 0;
        virtual void arrive() = 0;


        //virtual void handleCollision(std::string objId,std::string fixtureType,std::string self_fixtureType) = 0;
        int maxHealthLevel;
        int minHealthLevel;
        int currentHealthLevel;
        int damageAmount;

        float topSpeed;
        b2Vec2 b2V_velocity;
        b2Vec2 b2V_acceleration;
        b2Vec2 impactDirection;
        int impactDuration;

        MoveableBody* _physicsBody;
        AnimatableGraphic* _graphicsBody;
        RadiusBody* _alertRadius;
        //RadiusBody* _attackRadius;

        enum ImpactState
        {
            STUNNED,
            PUSHEDBACK,
            PULLED,
            NO_IMPACT
        }impactTypeState;

        enum AliveState
        {
            ALIVE,
            DEAD
        }aliveState;

        enum AttackState
        {
            NO_ATTACK
        }attackTypeState;



    protected:
    private:
};

#endif // ACTOR_H
