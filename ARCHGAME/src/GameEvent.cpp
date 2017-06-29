#include "GameEvent.h"

std::queue<GameEvent*> GameEventQueue;

GameEvent::GameEvent()
{
}

GameEvent::~GameEvent()
{
    //dtor
}

GameEvent::eventType GameEvent::getEventType()
{
    return event_type;
}
