#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

/**Entity interface class. Foundation for building entity objects with underlying functionality**/
///NOTE to self Create a base class for other entity types to inherit from entity
///Like A base Enemy class that uses data to drive it instead of creating a different class for each enemy
///Same goes for GameObjects so to speak(interactable objects)
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
