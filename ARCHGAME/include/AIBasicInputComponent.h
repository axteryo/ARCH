#ifndef AIBASICINPUTCOMPONENT_H
#define AIBASICINPUTCOMPONENT_H

#include <InputComponent.h>
#include "ActionComponent.h"


class AIBasicInputComponent : public InputComponent
{
    public:
        AIBasicInputComponent();
        virtual ~AIBasicInputComponent();
        void processInput(ActorEntity* a);
        void onNotifyEntityNearby(entity* e);
        void onNotifyEntityWithinRadius(entity* e);

        void setTarget(entity* t);
        void setAlert();
        void setAggro();


    private:
        bool isAlert;
        bool isAggro;

        entity* target;
};

#endif // AIBASICINPUTCOMPONENT_H
