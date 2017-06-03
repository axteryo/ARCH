#include "CollisionSystem.h"

CollisionSystem::CollisionSystem()
{
    //ctor
}

CollisionSystem::~CollisionSystem()
{
    //dtor
}
void CollisionSystem::notifyCollisionEvent(collisionEventData* colData)
{
    collisionEvents.push(colData);
}
void CollisionSystem::BeginContact(b2Contact* contact)
{
    entity* A;
    entity* B;
    fixtureUserData* dataA;
    fixtureUserData* dataB;
    A = static_cast<entity*>(contact->GetFixtureA()->GetBody()->GetUserData());
    B = static_cast<entity*>(contact->GetFixtureB()->GetBody()->GetUserData());
    dataA = static_cast<fixtureUserData*>(contact->GetFixtureA()->GetUserData());
    dataB = static_cast<fixtureUserData*>(contact->GetFixtureB()->GetUserData());

    if(A&&B&&dataA&&dataB)
    {
        collisionEventData* c = new collisionEventData(A,B,dataA,dataB,"COLLISION_INITIAL");
        collisionEvents.push(c);
    }
}
void CollisionSystem::EndContact(b2Contact* contact)
{
    entity* A;
    entity* B;
    fixtureUserData* dataA;
    fixtureUserData* dataB;
    A = static_cast<entity*>(contact->GetFixtureA()->GetBody()->GetUserData());
    B = static_cast<entity*>(contact->GetFixtureB()->GetBody()->GetUserData());
    dataA = static_cast<fixtureUserData*>(contact->GetFixtureA()->GetUserData());
    dataB = static_cast<fixtureUserData*>(contact->GetFixtureB()->GetUserData());
    if(A&&B&&dataA&&dataB)
    {
        collisionEventData* c = new collisionEventData(A,B,dataA,dataB,"COLLISION_END");
        notifyCollisionEvent(c);
    }
}
void CollisionSystem::resolveCollision()
{/*
   collisionEventData* colData = collisionEvents.front();
    std::string aType = colData->A->getType();
    std::string bType = colData->B->getType();
    std::string aFixtureType = colData->A_Data->type;
    std::string bFixtureType = colData->B_Data->type;



    if(colData->collisionType.compare("COLLISION_INITIAL")==0)
    {

        if(aType.compare("actor")==0)
        {
            ActorEntity* A = static_cast<ActorEntity*>(colData->A);

            if(bType.compare("actor")==0)
            {
                ActorEntity* B = static_cast<ActorEntity*>(colData->B);
                if(bFixtureType.compare("sensorFixture")==0)
                {
                    B->notifyActorWithinRange(A);
                }

                if(aFixtureType.compare("attackFixture")==0)
                {
                    if(bFixtureType.compare("bodyFixture")==0)
                    {
                        attackAttributeState attackAttributes_A = A->getStates()->getAttackAttributeState();
                        applyAttackCollision(attackAttributes_A,B);
                    }
                }
                else if(aFixtureType.compare("bodyFixture")==0)
                {
                    if(bFixtureType.compare("attackFixture")==0)
                    {
                        if(aFixtureType.compare("bodyFixture")==0)
                        {
                            attackAttributeState attackAttributes_B = B->getStates()->getAttackAttributeState();
                            applyAttackCollision(attackAttributes_B,A);
                        }
                    }
                }
                else if(aFixtureType.compare("sensorFixture")==0)
                {
                    A->notifyActorWithinRange(B);
                }

            }


        }
        else if(aType.compare("object")==0)
        {

        }
    }
    delete colData;*/
}
void CollisionSystem::update()
{
    for(int i = 0;i<collisionEvents.size();i++)
    {
        collisionEventData* colData = collisionEvents.front();
        if(colData->collisionType.compare("COLLISION_INITIAL")==0)
        {
            if(colData->entityA!=nullptr && colData->entityB!=nullptr)
            {
                colData->entityA->initiateCollision(colData->entityB,colData->B_Data,colData->A_Data);
                colData->entityB->initiateCollision(colData->entityA,colData->A_Data,colData->B_Data);
            }

        }
        delete colData;
        collisionEvents.pop();
    }
}

void CollisionSystem::applyAttackCollision(attackAttributeState a, ActorEntity* A)
{
    impactAttributeState i = A->getStates()->getImpactAttributeState();
    i.force = a.force;
    i.impactDamage = a.damage;
    i.impactDuration = a.impactDuration;
    i.impactType = a.impactType;
    i.direction = a.direction;
    i.isImpacted = true;
    A->getStates()->setImpactAttributeState(i);
}


