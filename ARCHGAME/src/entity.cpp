#include "entity.h"
#include "PhysicsComponent.h"



entity::entity()
{
    deathFlag = 0;
}

entity::~entity()
{
    //dtor
}
/****BASE ENTITY FUNCTIONS*****/
void entity::setPosition(b2Vec2 p)
{
    physics_component->setPosition(p);
}
b2Vec2 entity::getPosition()
{
    return physics_component->getPosition();
}
void entity::setRotation(float a)
{
    physics_component->setRotation(a);
}
float entity::getRotation()
{
    return physics_component->getRotation();
}
std::string entity::getID()
{
    return entity_ID;
}
std::string entity::getType()
{
    return entityType;
}
std::string entity::getTag()
{
    return entityTag;
}

void entity::raiseDeathFlag()
{
    deathFlag = 1;
}
int entity::getDeathFlag()
{
    return deathFlag;
}

PhysicsComponent* entity::getPhysics()
{
    return physics_component;
}


/**UPDATE FUNCTION**/

positionState entity::getCurrentState()
{
    return physics_component->getCurrentState();
}
positionState entity::getPreviousState()
{
    return physics_component->getPreviousState();
}

