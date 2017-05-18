#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include "entity.h"

#include <iostream>

class ActorEntity;


class InputComponent
{
    public:
        InputComponent();
        virtual ~InputComponent();
        virtual void processInput(ActorEntity* a)=0;
        virtual void onNotifyEntityNearby(entity* e)=0;
        virtual void onNotifyEntityWithinRadius(entity* e)=0;
    protected:
    private:
};

#endif // INPUTCOMPONENT_H
