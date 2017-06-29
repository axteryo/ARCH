#ifndef ACTORENTITY_H
#define ACTORENTITY_H

#include "entity.h"
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"
#include "AttackAction.h"
//#include "StateComponent.h"
//#include "ActionComponent.h"
#include "playerInputComponent.h"
#include "AIBasicInputComponent.h"
#include "GameEventListener.h"

class ActionComponent;


extern std::stack<entity*> deathStack;


class ActorEntity : public entity
{
    public:
        ActorEntity(std::string e_ID,GraphicsComponent* g,PhysicsComponent* p,InputComponent* i,StateComponent* s, ActionComponent* a,GameEventListener* eListener);
        virtual ~ActorEntity();

        float getTopSpeed();

        void update();

        movementAttributeState getMovementAttributeState();
        statusAttributeState getStatusAttributeState();
        attackAttributeState getAttackAttributeState();
        impactAttributeState getImpactAttributeState();


        void notifyEntityNearby(entity* e);
        void notifyEntityWithinRadius(entity* e);
        void notifyBodyCollision(entity* e);

        bool isAttacking();
        bool isRotating();
        bool isAlive();
        bool isAccelerating();
        bool isImpacted();
        bool isBoosting();
        bool inGridMode();

        /**
        virtual void initiateCollision() = 0;
        virtual void resolveCollision() = 0;
        **/

        GraphicsComponent* getGraphics();
        //PhysicsComponent* getPhysics();
        StateComponent* getStates();
        ActionComponent* getActions();

        void initiateCollision(entity* other, fixtureUserData* otherFData, fixtureUserData* selfFData);
        void applyAttackOnSelf(attackFixtureUserData* a);
        void playAnimation(std::string animation,bool byTag);

        GameEventListener* _listener;


    protected:
    private:
        GraphicsComponent* graphics_component;
        //PhysicsComponent* physics_component;
        InputComponent* input_component;
        StateComponent* state_component;
        ActionComponent* action_component;

        //std::vector<attackData> registeredAttacks;
        //States::attributeState attributes;

};

#endif // ACTORENTITY_H
