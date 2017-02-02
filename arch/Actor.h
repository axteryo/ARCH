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

        virtual void update() = 0;
        virtual void setPosition(float x, float y) = 0;
        virtual b2Vec2 getPosition() = 0;
        virtual void setRotation(float angle) = 0;
        virtual sf::Sprite getSprite() = 0;


        //virtual void handleCollision(std::string objId,std::string fixtureType,std::string self_fixtureType) = 0;


        float topSpeed;
        b2Vec2 b2V_velocity;
        b2Vec2 b2V_acceleration;
        b2Vec2 impactDirection;

        MoveableBody* _physicsBody;
        AnimatableGraphic* _graphicsBody;
        RadiusBody* _alertRadius;
        RadiusBody* _attackRadius;

        enum ImpactState
        {
            STUNNED,
            PUSHEDBACK,
            NO_IMPACT
        }impactTypeState;

    protected:
    private:
};

#endif // ACTOR_H
