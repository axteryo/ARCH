#ifndef ACTORENTITY_H
#define ACTORENTITY_H

#include "entity.h"
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"
//#include "ActionComponent.h"
#include "playerInputComponent.h"
#include "AIBasicInputComponent.h"

class ActionComponent;




class ActorEntity : public entity
{
    public:
        ActorEntity(std::string e_ID,GraphicsComponent* g,PhysicsComponent* p,InputComponent* i,StateComponent* s, ActionComponent* a);
        virtual ~ActorEntity();

        void setPosition(b2Vec2 p);
        void setRotation(float a);
        b2Vec2 getPosition();
        float getRotation();

        void update();
        std::string getID();
        std::string getType();

        positionState getCurrentState();
        positionState getPreviousState();
        //moattributeState getAttributes();

        /**
        virtual void initiateCollision() = 0;
        virtual void resolveCollision() = 0;
        **/

        //void setAttributes(States::attributeState a);


        GraphicsComponent* getGraphics();
        PhysicsComponent* getPhysics();
        StateComponent* getStates();
        ActionComponent* getActions();



        ///State Functions
        void setRotateRightState();
        void setRotateLeftState();
        void setRotateRightStateFalse();
        void setRotateLeftStateFalse();
        void setAccelState();
        void setAccelStateFalse();
        void setBrakeState();
        void setBrakeStateFalse();

         enum RotateRightState
        {
            ROTATE_RIGHT,
            ROTATE_RIGHT_F
        }rotateRightState;
         enum RotateLefttState
        {
            ROTATE_LEFT,
            ROTATE_LEFT_F
        }rotateLeftState;
        enum AccelState
        {
            ACCELERATE,
            ACCELERATE_F
        }accelState;
        enum BrakeState
        {
            BRAKE,
            BRAKE_F

        }brakeState;


    protected:
    private:
        GraphicsComponent* graphics_component;
        PhysicsComponent* physics_component;
        InputComponent* input_component;
        StateComponent* state_component;
        ActionComponent* action_component;

        //std::vector<attackData> registeredAttacks;
        //States::attributeState attributes;

};

#endif // ACTORENTITY_H
