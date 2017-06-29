#include "GameEventListener.h"
//#include "GameEvent.h"



GameEventListener::GameEventListener()
{
    //ctor
}

GameEventListener::~GameEventListener()
{
    //dtor
}

void GameEventListener::notifyEvent(GameEvent* g)
{
    GameEventQueue.push(g);
}
