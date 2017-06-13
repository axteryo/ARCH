#include "TriggerEntity.h"
#include "PhysicsComponent.h"
#include "SequenceEntity.h"

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
void TriggerEntity::addSequence(SequenceEntity* e)
{
    sequenceList.push_back(e);
}

void TriggerEntity::sequenceBegin()
{

    for(int i = 0;i<sequenceList.size();++i)
    {
        sequenceList[i]->onSequenceBegin();
    }
    raiseDeathFlag();
}

/**UPDATE FUNCTION**/
void TriggerEntity::update()
{
    physics_component->update();
    if(deathFlag>0)
    {
        //world->DestroyBody(physics_component->getBody());
        physics_component->getBody()->SetActive(false);
        deathStack.push(this);
        //deathFlag = 0;
    }
}

void TriggerEntity::initiateCollision(entity* other, fixtureUserData* otherFData, fixtureUserData* selfFData)
{
    ///Actor to Actor collision
    if(other->getID().compare("entity_player")==0)
    {
        if(otherFData->type.compare("bodyFixture")==0)
        {
            sequenceBegin();
        }
    }
}


