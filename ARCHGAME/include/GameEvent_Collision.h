#ifndef GAMEEVENT_COLLISION_H
#define GAMEEVENT_COLLISION_H

#include <GameEvent.h>
#include "PhysicsComponent.h"
class entity;


class GameEvent_Collision : public GameEvent
{
    public:
        GameEvent_Collision(entity* a, entity* b, fixtureUserData* dataA, fixtureUserData* dataB,std::string colType);
        virtual ~GameEvent_Collision();

    std::string collisionType;
    entity* entityA;
    entity* entityB;

    fixtureUserData* A_Data;
    fixtureUserData* B_Data;
    protected:
    private:
};

#endif // GAMEEVENT_COLLISION_H
