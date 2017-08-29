#include "GameEvent_Interface.h"

GameEvent_Interface::GameEvent_Interface(InterfaceState i,std::string bID)
{
    event_type = EVENT_INTERFACE;
    interface_state=i;
    btnID = bID;
}

GameEvent_Interface::~GameEvent_Interface()
{
    //dtor
}
