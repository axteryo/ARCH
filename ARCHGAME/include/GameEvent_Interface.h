#ifndef GAMEEVENT_INTERFACE_H
#define GAMEEVENT_INTERFACE_H

#include <GameEvent.h>
enum InterfaceState
{
    BUTTON_OVER,
    BUTTON_SELECT
};

class GameEvent_Interface : public GameEvent
{
    public:
        GameEvent_Interface(InterfaceState i);
        virtual ~GameEvent_Interface();
        InterfaceState interface_state;
    protected:
    private:
};

#endif // GAMEEVENT_INTERFACE_H
