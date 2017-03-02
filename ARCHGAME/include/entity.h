#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>


class entity
{
    public:
        entity();
        virtual ~entity()=0;
        virtual void setPosition(b2Vec2 p)=0;
        virtual void setRotation(float a)=0;
        virtual b2Vec2 getPosition()=0;
        virtual float getRotation()=0;

        virtual void update(float dt) = 0;
        virtual void physicsUpdate(float dt)= 0;
        virtual std::string getID() = 0;
        /**
        virtual void initiateCollision() = 0;
        virtual void resolveCollision() = 0;
        **/
    protected:
        std::string entity_ID;
    private:

};

#endif // ENTITY_H