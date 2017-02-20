#include "Ai_Controller.h"

Ai_Controller::Ai_Controller()
{
    Game_Event = NOTHING;
    Ai_Routine = IDLE;
}

Ai_Controller::~Ai_Controller()
{
    //dtor
}

void Ai_Controller::onNotify(GameEvent e,const GameObject& gObj)
{

}

void Ai_Controller::initiateRoutine(Enemy_D1* e)
{

}
