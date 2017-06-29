#ifndef ENTITY_H
#define ENTITY_H


#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "StateComponent.h"
#include <stack>
#include "GameEvent_Entity.h"

class PhysicsComponent;
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
        virtual void setPosition(b2Vec2 p);
        virtual void setRotation(float a);
        virtual b2Vec2 getPosition();
        virtual float getRotation();

        virtual void update() = 0;
        virtual std::string getID();
        virtual std::string getType();
        virtual std::string getTag();
        virtual void raiseDeathFlag();
        virtual int getDeathFlag();

        virtual positionState getCurrentState();
        virtual positionState getPreviousState();

        virtual PhysicsComponent* getPhysics();

        virtual void initiateCollision(entity* other, fixtureUserData* otherFData, fixtureUserData* selfFData) = 0;
        //virtual void endCollision() = 0;


    protected:
        int deathFlag;
        std::string entity_ID;
        std::string entityType;
        std::string entityTag;
        PhysicsComponent* physics_component;

    private:

};

#endif // ENTITY_H
