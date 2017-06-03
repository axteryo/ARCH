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
                if(!a->isAttacking())
                {

                fixtureUserData* fData = new fixtureUserData;
                elapsed = data.duration;
                fData->type = data.fixtureType;
                fData->data = data.fixtureData;
                PhysicsComponent* p = new PhysicsComponent(b2_kinematicBody);

                attackFixture = p->createFixturePolygon(data.shape,data.relPosition,fData,data.isSensor);


                ProjectileEntity* pr = new ProjectileEntity("entity_projectile",p);
                pr->setRotation(a->getRotation());
                pr->setPosition(a->getPosition());
                pr->update();
                projectileList.push_back(pr);

                float r = a->getRotation();
                b2Vec2 acceleration = b2Vec2(0,0);




                acceleration = b2Vec2(cos(r),sin(r));
                acceleration.Normalize();
                acceleration.x*=50;
                acceleration.y*=50;
                p->accelerate(acceleration);

                isActive = true;
/*
                attackState.attack = data.name;
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

void BeamAttackAction::update(ActorEntity* a)
{
    elapsed-=1;

    if(inCoolDown)
    {
        if(elapsed<0)
        {
            isActive = false;
            inCoolDown = false;
            elapsed = 0;
            for(int i = 0;i<projectileList.size();i++)
            {

                delete projectileList[i];
            }
            projectileList.clear();
            attackFixture = nullptr;

        }
    }
    else
    {
        for(int i = 0;i<projectileList.size();i++)
        {

            projectileList[i]->update();
        }
        if(elapsed<0)
        {
            //a->getPhysics()->getBody()->DestroyFixture(attackFixture);
            inCoolDown = true;
            elapsed = data.coolDown;
            //attackFixture = nullptr;
        }
    }
}

