#ifndef ENTITY_H
#define ENTITY_H


#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "StateComponent.h"
#include "PhysicsComponent.h"

struct fixtureUserData;

/**Entity interface class. Foundation for building entity objects with underlying functionality**/
///NOTE to self Create a base class for other entity types to inherit from entity
///Like A base ActorEntity class that uses data to drive it instead of creating a different class for each enemy
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

        virtual void update() = 0;
        virtual std::string getID() = 0;
        virtual std::string getType()=0;

        virtual positionState getCurrentState()= 0;
        virtual positionState getPreviousState()= 0;

        virtual void initiateCollision(entity* other, fixtureUserData* otherFData, fixtureUserData* selfFData) = 0;
        //virtual void endCollision() = 0;

    protected:
        std::string entity_ID;
        std::string entityType;
        std::string entityTag;
    private:

};

#endif // ENTITY_H
