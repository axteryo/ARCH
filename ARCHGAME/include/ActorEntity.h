#ifndef ACTORENTITY_H
#define ACTORENTITY_H

#include "entity.h"
#include "GraphicsComponent.h"
//#include "PhysicsComponent.h"
//#include "StateComponent.h"
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
        float getTopSpeed();

        void update();
        std::string getID();
        std::string getType();

        positionState getCurrentState();
        positionState getPreviousState();
        movementAttributeState getMovementAttributeState();
        statusAttributeState getStatusAttributeState();
        attackAttributeState getAttackAttributeState();
        impactAttributeState getImpactAttributeState();


        void notifyEntityNearby(entity* e);
        void notifyEntityWithinRadius(entity* e);

        bool isAttacking();
        bool isRotating();
        bool isAlive();
        bool isAccelerating();
        bool isImpacted();

        /**
        virtual void initiateCollision() = 0;
        virtual void resolveCollision() = 0;
        **/

        GraphicsComponent* getGraphics();
        PhysicsComponent* getPhysics();
        StateComponent* getStates();
        ActionComponent* getActions();

        void initiateCollision(entity* other, fixtureUserData* otherFData, fixtureUserData* selfFData);
        void applyAttackOnSelf(attackAttributeState a);
        void playAnimation(std::string animation,bool byTag);


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
