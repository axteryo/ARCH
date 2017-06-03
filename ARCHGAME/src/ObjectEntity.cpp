#include "ObjectEntity.h"

ObjectEntity::ObjectEntity(std::string e_ID, PhysicsComponent* p)
{
    entity_ID = e_ID;
    entityType = "object";
    physics_component = p;
    physics_component->getBody()->SetUserData((void*)this);
    deathFlag = 0;

    //ctor
}

ObjectEntity::~ObjectEntity()
{
    delete physics_component;
    //dtor
}


/**UPDATE FUNCTION**/
void ObjectEntity::update()
{
    physics_component->update();
}

void ObjectEntity::initiateCollision(entity* other, fixtureUserData* otherFData, fixtureUserData* selfFData)
{

}



