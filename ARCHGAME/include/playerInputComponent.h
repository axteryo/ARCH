#ifndef PLAYERINPUTCOMPONENT_H
#define PLAYERINPUTCOMPONENT_H


#include "GameController.h"
#include "InputComponent.h"
#include "ActorEntity.h"
#include "AccelerateAction.h"
#include "BrakeAction.h"
#include "RotateLeftAction.h"
#include "RotateRightAction.h"



extern GameController controller;



class playerInputComponent: public InputComponent
{
    public:
        playerInputComponent();
        virtual ~playerInputComponent();
        void processInput(ActorEntity* a);
    protected:
    private:
       AccelerateAction _accelerate;
       RotateLeftAction _rotateLeft;
       RotateRightAction _rotateRight;
       BrakeAction _brake;

};

#endif // PLAYERINPUTCOMPONENT_H
