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
        void onNotifyBodyCollision(entity* e);

        void setTarget(entity* t);
        void setAlert();
        void setAggro();

        std::string steerDirection(b2Vec2 targPos, b2Vec2 selfPos,float selfRotation);


    private:
        bool isAlert;
        bool isAggro;
        bool accelerate;

        entity* target;
};

#endif // AIBASICINPUTCOMPONENT_H
