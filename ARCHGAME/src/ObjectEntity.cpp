#include "ObjectEntity.h"

ObjectEntity::ObjectEntity(std::string e_ID, PhysicsComponent* p)
{
    entity_ID = e_ID;
    entityType = "object";
    physics_component = p;
    physics_component->getBody()->SetUserData((void*)this);

    //ctor
}

ObjectEntity::~ObjectEntity()
{
    delete physics_component;
    //dtor
}

PhysicsComponent* ObjectEntity::getPhysics()
{
    return physics_component;
}
/****BASE ENTITY FUNCTIONS*****/
void ObjectEntity::setPosition(b2Vec2 p)
{
    physics_component->setPosition(p);
}
b2Vec2 ObjectEntity::getPosition()
{
    return physics_component->getPosition();
}
void ObjectEntity::setRotation(float a)
{
    physics_component->setRotation(a);
}
float ObjectEntity::getRotation()
{
    return physics_component->getRotation();
}
std::string ObjectEntity::getID()
{
    return entity_ID;
}
std::string ObjectEntity::getType()
{
    return entityType;
}

/**UPDATE FUNCTION**/
void ObjectEntity::update()
{
    physics_component->update();
}


positionState ObjectEntity::getCurrentState()
{
    return physics_component->getCurrentState();
}
positionState ObjectEntity::getPreviousState()
{
    return physics_component->getPreviousState();
}



