#include "AttackAction.h"

#include "ActorEntity.h"


AttackAction::AttackAction()
{
    elapsed = 0;
    attackFixture = nullptr;
}

AttackAction::~AttackAction()
{
    //dtor
}

void AttackAction::setData(attackData aData)
{
    data.name=aData.name;
    data.attackType= aData.attackType;
    data.duration= aData.duration;
    data.coolDown= aData.coolDown;
    data.rotationRate= aData.rotationRate;
    data.shape= aData.shape;
    data.damage = aData.damage;
    data.force = aData.force;
    data.impactDuration = aData.impactDuration;
    data.impactType= aData.impactType;
    data.fixtureType= aData.fixtureType;
    data.fixtureData= aData.fixtureData;
    data.isSensor= aData.isSensor;
    data.graphic = aData.graphic;

    actionType = aData.attackType;

}

void AttackAction::update(ActorEntity* a)
{

    elapsed-=1;
    if(inCoolDown)
    {

        if(elapsed<0)
        {
            isActive = false;
            inCoolDown = false;
            elapsed = 0;
            attackState.attack = "";
            attackState.damage = 0;
            attackState.force= 0;
            attackState.impactType = "";
            attackState.isAttacking = false;
            a->getStates()->setAttackAttributeState(attackState);
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
        else
        {
                attackState.attack = data.name;
                attackState.damage = data.damage;
                attackState.impactDuration = data.impactDuration;
                attackState.force = data.force;
                attackState.impactType = data.impactType;
                attackState.isAttacking = true;
                float r = a->getRotation();
                attackState.direction = b2Vec2(cos(r),sin(r));
                attackState.direction.Normalize();
                a->getStates()->setAttackAttributeState(attackState);

        }
    }


}
