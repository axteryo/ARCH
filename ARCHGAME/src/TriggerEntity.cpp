#include "TriggerEntity.h"
#include "PhysicsComponent.h"

TriggerEntity::TriggerEntity(std::string e_ID, std::string e_tag,PhysicsComponent* p)
{
    entity_ID = e_ID;
    entityType = "trigger";
    entityTag = e_tag;
    physics_component = p;
    physics_component->getBody()->SetUserData((void*)this);
    deathFlag = 0;

}

TriggerEntity::~TriggerEntity()
{
    delete physics_component;
}

/**UPDATE FUNCTION**/
void TriggerEntity::update()
{
    physics_component->update();
}

void TriggerEntity::initiateCollision(entity* other, fixtureUserData* otherFData, fixtureUserData* selfFData)
{

}


