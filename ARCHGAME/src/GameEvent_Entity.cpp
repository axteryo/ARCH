#include "GameEvent_Entity.h"
#include "entity.h"

GameEvent_Entity::GameEvent_Entity(entity* e, EntityState eState)
{
    event_type = EVENT_ENTITY;
    _entity = e;
    entity_state = eState;
}

GameEvent_Entity::~GameEvent_Entity()
{
    //dtor
}
