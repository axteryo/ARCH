#include "TriggerEntity.h"

TriggerEntity::TriggerEntity(std::string e_ID, std::string e_tag,PhysicsComponent* p)
{
    entity_ID = e_ID;
    entityType = "trigger";
    physics_component = p;
    physics_component->getBody()->SetUserData((void*)this);

}

TriggerEntity::~TriggerEntity()
{
    delete physics_component;
}

/****BASE ENTITY FUNCTIONS*****/
void TriggerEntity::setPosition(b2Vec2 p)
{
    physics_component->setPosition(p);
}
b2Vec2 TriggerEntity::getPosition()
{
    return physics_component->getPosition();
}
void TriggerEntity::setRotation(float a)
{
    physics_component->setRotation(a);
}
float TriggerEntity::getRotation()
{
    return physics_component->getRotation();
}
std::string TriggerEntity::getID()
{
    return entity_ID;
}
std::string TriggerEntity::getType()
{
    return entityType;
}

/**UPDATE FUNCTION**/
void TriggerEntity::update()
{
    physics_component->update();
}


positionState TriggerEntity::getCurrentState()
{
    return physics_component->getCurrentState();
}
positionState TriggerEntity::getPreviousState()
{
    return physics_component->getPreviousState();
}

void TriggerEntity::initiateCollision(entity* other, fixtureUserData* otherFData, fixtureUserData* selfFData)
{

}


