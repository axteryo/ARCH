#ifndef PLAYERINPUTCOMPONENT_H
#define PLAYERINPUTCOMPONENT_H


#include "GameController.h"
#include <InputComponent.h>
#include "ActionComponent.h"




extern GameController controller;



class playerInputComponent: public InputComponent
{
    public:
        playerInputComponent();
        virtual ~playerInputComponent();
        void processInput(ActorEntity* a);
        void onNotifyEntityNearby(entity* e);
        void onNotifyEntityWithinRadius(entity* e);
        void onNotifyBodyCollision(entity* e);
    protected:
    private:
       //AccelerateAction _accelerate;
       //RotateLeftAction _rotateLeft;
       //RotateRightAction _rotateRight;
       //BrakeAction _brake;
       //DeccelerateAction _deccelerate;

};

#endif // PLAYERINPUTCOMPONENT_H
