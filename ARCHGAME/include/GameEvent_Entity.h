#ifndef GAMEEVENT_ENTITY_H
#define GAMEEVENT_ENTITY_H

#include <GameEvent.h>
class entity;
enum EntityState
{
    ENTITY_DIED
};

class GameEvent_Entity: public GameEvent
{
    public:
        GameEvent_Entity(entity* e, EntityState eState);

        entity* _entity;
        EntityState entity_state;


        virtual ~GameEvent_Entity();

    protected:
    private:
};

#endif // GAMEEVENT_ENTITY_H
