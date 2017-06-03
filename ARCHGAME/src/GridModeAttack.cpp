#include "GridModeAttack.h"

GridModeAttack::GridModeAttack()
{
    elapsed = 0;
    actionType = "";
    inCoolDown = false;
    attackFixture = nullptr;
    isActive = false;
}

GridModeAttack::~GridModeAttack()
{
    //dtor
}


void GridModeAttack::execute(ActorEntity* a)
{
    if(!inCoolDown)
    {
        if(elapsed<=0)
        {
            if(!isActive)
            {


                elapsed = data.duration;

                movementAttributeState m = a->getMovementAttributeState();
               m.inGridMode = true;
                a->getStates()->setMovementAttributeState(m);




                /*float r = a->getRotation();
                b2Vec2 acceleration = b2Vec2(0,0);




                acceleration = b2Vec2(cos(r),sin(r));
                acceleration.Normalize();
                acceleration.x*=50;
                acceleration.y*=50;*/
                //p->accelerate(acceleration);

                isActive = true;
                attackState.attack = data.name;
                attackState.damage = data.damage;
                attackState.impactDuration = data.impactDuration;
                attackState.force = data.force;
                attackState.impactType = data.impactType;
                attackState.rotationRate = data.rotationRate;
                attackState.isAttacking = true;
                a->getStates()->setAttackAttributeState(attackState);
            }
            else
            {
                //cancel();
            }
        }
    }
}

void GridModeAttack::update(ActorEntity* a)
{
    elapsed-=1;

    if(inCoolDown)
    {
        if(elapsed<0)
        {

            inCoolDown = false;
            isActive = false;
            elapsed = 0;
            //
        }
    }
    else
    {
        if(a->isBoosting())
        {
            //int index = projectileList.size()-1;
            for(int i = 0;i<projectileList.size();i++)
            {
            projectileList[i]->update();
            }
            fixtureUserData* fData = new fixtureUserData;
            fData->type = data.fixtureType;
            fData->data = data.fixtureData;
            PhysicsComponent* p = new PhysicsComponent(b2_kinematicBody);

            p->createFixturePolygon(data.shape,data.relPosition,fData,data.isSensor);

            ProjectileEntity* pr = new ProjectileEntity("entity_projectile",p);

            pr->setPosition(a->getPosition());
            pr->update();
            projectileList.push_back(pr);
            //std::cout<<projectileList.size()<<std::endl;
        }
        if(elapsed<0)
        {
            for(int i = projectileList.size()-1;i>=0;--i)
            {
           // std::cout<<i<<std::endl;
            //delete projectileList[i];
            projectileList[i]->raiseDeathFlag();
            deathStack.push(projectileList[i]);
            }
            projectileList.clear();
            std::cout<<"break"<<std::endl;

            movementAttributeState m = a->getMovementAttributeState();
            m.inGridMode = false;
            a->getStates()->setMovementAttributeState(m);

            inCoolDown = true;
            elapsed = data.coolDown;
            attackFixture = nullptr;
            attackState.attack = "";
            attackState.damage = 0;
            attackState.force= 0;
            attackState.impactType = "";
            attackState.isAttacking = false;
            a->getStates()->setAttackAttributeState(attackState);
        }
    }
}
