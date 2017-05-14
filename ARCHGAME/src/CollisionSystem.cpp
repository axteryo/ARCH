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

        notifyCollisionEvent(c);
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
{
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
                if(aFixtureType.compare("attackFixture")==0)
                {
                    attackAttributeState attackAttributes_A = A->getStates()->getAttackAttributeState();

                    if(bFixtureType.compare("bodyFixture")==0)
                    {

                        applyAttackCollision(attackAttributes_A,B);
                    }
                }
                else if(aFixtureType.compare("bodyFixture")==0)
                {
                    if(bFixtureType.compare("attackFixture")==0)
                    {
                        attackAttributeState attackAttributes_B = B->getStates()->getAttackAttributeState();

                        if(aFixtureType.compare("bodyFixture")==0)
                        {

                            applyAttackCollision(attackAttributes_B,A);
                        }
                    }
                }

            }


        }
        else if(aType.compare("object")==0)
        {

        }
    }
    delete colData;
}
void CollisionSystem::update()
{

    for(int i = 0;i<collisionEvents.size();i++)
    {
        resolveCollision();
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


