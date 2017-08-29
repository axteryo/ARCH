#ifndef GAMEEVENT_INTERFACE_H
#define GAMEEVENT_INTERFACE_H

#include <GameEvent.h>
#include <string>
enum InterfaceState
{
    BUTTON_OVER,
    BUTTON_SELECT
};

class GameEvent_Interface : public GameEvent
{
    public:
        GameEvent_Interface(InterfaceState i,std::string bID);
        virtual ~GameEvent_Interface();
        InterfaceState interface_state;
        std::string btnID;
    protected:
    private:
};

#endif // GAMEEVENT_INTERFACE_H
