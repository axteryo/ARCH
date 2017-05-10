#include "BeamAttackAction.h"
#include "ActorEntity.h"

BeamAttackAction::BeamAttackAction()
{
    elapsed = 0;
    actionType = "";
    inCoolDown = false;
    attackFixture = nullptr;
    isActive = false;
}

BeamAttackAction::~BeamAttackAction()
{
    //dtor
}

void BeamAttackAction::execute(ActorEntity* a)
{
    if(!inCoolDown)
    {
        if(elapsed<=0)
        {
            if(!attackFixture)
            {
                fixtureUserData* fData = new fixtureUserData;
                elapsed = data.duration;
                fData->type = data.fixtureType;
                fData->data = data.fixtureData;
                attackFixture = a->getPhysics()->createFixturePolygon(data.shape,b2Vec2(-100,100),fData,data.isSensor);
                isActive = true;
            }
        }
    }
}

/*void BeamAttackAction::update(ActorEntity* a)
{
    elapsed-=1;
    if(inCoolDown)
    {


        if(elapsed<0)
        {
            isActive = false;
            inCoolDown = false;
            elapsed = data.duration;
        }
    }
    else
    {
        if(elapsed<0)
        {
            a->getPhysics()->getBody()->DestroyFixture(attackFixture);
            inCoolDown = true;
            elapsed = data.coolDown;
            attackFixture = nullptr;
        }
    }
}*/

