#include "ProjectileEntity.h"
#include "PhysicsComponent.h"

ProjectileEntity::ProjectileEntity(std::string e_ID, PhysicsComponent* p)
{
    entity_ID = e_ID;
    entityType = "projectile";
    physics_component = p;
    physics_component->getBody()->SetUserData((void*)this);
    p->setTopSpeed(100);
    deathFlag = 0;

    //ctor
}

ProjectileEntity::~ProjectileEntity()
{
    delete physics_component;
    //dtor
}


/**UPDATE FUNCTION**/
void ProjectileEntity::update()
{
    physics_component->update();
}


void ProjectileEntity::initiateCollision(entity* other, fixtureUserData* otherFData, fixtureUserData* selfFData)
{

}



