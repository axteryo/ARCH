#include "GameEvent_Collision.h"
#include "entity.h"

GameEvent_Collision::GameEvent_Collision(entity* a, entity* b, fixtureUserData* dataA, fixtureUserData* dataB,std::string colType)
{
    event_type = EVENT_COLLISION;
    entityA = a;
    entityB = b;
    A_Data = dataA;
    B_Data = dataB;
    collisionType = colType;
}

GameEvent_Collision::~GameEvent_Collision()
{
    //dtor
}
