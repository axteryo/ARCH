#include "RadiusAttackAction.h"
#include "ActorEntity.h"

RadiusAttackAction::RadiusAttackAction()
{
    elapsed = 0;
    actionType = "";
    inCoolDown = false;
    attackFixture = nullptr;
    isActive = false;
}

RadiusAttackAction::~RadiusAttackAction()
{
    //dtor
}

void RadiusAttackAction::execute(ActorEntity* a)
{
    if(!inCoolDown)
    {
        if(elapsed<=0)
        {
            if(!attackFixture)
            {
                if(!a->isAttacking())
                {
                //fixtureUserData* fData = new fixtureUserData;
                elapsed = data.duration;

                isActive = true;

                attackFixtureUserData* fData = new attackFixtureUserData;
                fData->type = data.fixtureType;
                fData->data = data.fixtureData;
                fData->force = data.force;
                fData->impactType = data.impactType;
                fData->impactDuration = data.impactDuration;
                fData->attackType = data.attackType;
                fData->direction = a->getPosition();
                fData->damage = data.damage;
                attackFixture = a->getPhysics()->createFixtureCircle(data.shape[0],b2Vec2(0,0),fData,data.isSensor);

                /*attackState.attack = data.name;
                attackState.damage = data.damage;
                attackState.impactDuration = data.impactDuration;
                attackState.force = data.force;
                attackState.impactType = data.impactType;
                attackState.isAttacking = true;
                a->getStates()->setAttackAttributeState(attackState);*/
                }
            }
        }
    }
}
