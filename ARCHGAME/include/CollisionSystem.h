#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include <Box2D/Box2D.h>
#include <queue>
#include "entity.h"
#include "ObjectEntity.h"
#include "ActorEntity.h"
#include "PhysicsComponent.h"

struct collisionEventData
{

    std::string collisionType = "";
    entity* entityA;
    entity* entityB;

    fixtureUserData* A_Data;
    fixtureUserData* B_Data;

    collisionEventData(entity* a, entity* b, fixtureUserData* dataA, fixtureUserData* dataB,std::string colType)
    {
        entityA = a;
        entityB = b;
        A_Data = dataA;
        B_Data = dataB;
        collisionType = colType;
    }

};

class CollisionSystem : public b2ContactListener
{
    public:
        CollisionSystem();
        virtual ~CollisionSystem();
        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);
        void Contact(b2Contact* contact);
        void notifyCollisionEvent(collisionEventData* colData);
        bool checkObstaclesBetween(entity* A, entity* B);
        void resolveCollision();

        void applyAttackCollision(attackAttributeState a, ActorEntity* A);
        void update();
    protected:
    private:
        std::queue<collisionEventData*> collisionEvents;

};

#endif // COLLISIONSYSTEM_H
