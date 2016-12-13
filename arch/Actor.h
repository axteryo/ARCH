#ifndef ACTOR_H
#define ACTOR_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "GameObject.h"
#include "includes.h"

class MoveableBody;
class AnimatableGraphic;



class Actor:public GameObject
{
    public:
        Actor();
        virtual ~Actor();

        virtual void update() = 0;
        virtual void setPosition(float x, float y) = 0;
        virtual sf::Sprite getSprite() = 0;


        float topSpeed;
        b2Vec2 b2V_velocity;

        MoveableBody* _physicsBody;
        AnimatableGraphic* _graphicsBody;

    protected:
    private:
};

#endif // ACTOR_H
