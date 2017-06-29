#ifndef GAMEEVENTLISTENER_H
#define GAMEEVENTLISTENER_H

#include "entity.h"
#include "GameEvent.h"

class GameEventListener
{
    public:
        GameEventListener();
        virtual ~GameEventListener();
        void notifyEvent(GameEvent* g);
    protected:
    private:
};

#endif // GAMEEVENTLISTENER_H
