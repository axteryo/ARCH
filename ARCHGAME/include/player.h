#ifndef PLAYER_H
#define PLAYER_H

#include "GameController.h"
//#include "playerInputComponent.h"
#include "entity.h"
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"



class playerInputComponent;

extern GameController controller;


class player : public entity
{
    public:
        player(GraphicsComponent* g,PhysicsComponent* p);
        virtual ~player();
        void setPosition(b2Vec2 p);
        void setRotation(float a);
        b2Vec2 getPosition();
        float getRotation();

        void update(float dt);

        GraphicsComponent* getGraphic();
        PhysicsComponent* getPhysics();
        /**
        virtual void initiateCollision() = 0;
        virtual void resolveCollision() = 0;
        **/
        std::string getID();

        ///State Functions
        void setTurnRightState();
        void setTurnLeftState();
        void setTurnRightStateFalse();
        void setTurnLeftStateFalse();
        void setThrustState();
        void setThrustStateFalse();
        void setBrakeState();
        void setBrakeStateFalse();

        ///Action Functions
        void turnRight();
        void turnLeft();
        void thrust();
        void brake();


    protected:
    private:
        GraphicsComponent* gComponent;
        PhysicsComponent* pComponent;
        playerInputComponent* inputComponent;

        float thrustRate;
        float turnRate;


         enum TurnRightState
        {
            TURN_RIGHT,
            TURN_RIGHT_F
        }tRightState;
          enum TurnLeftState
        {
            TURN_LEFT,
            TURN_LEFT_F
        }tLeftState;
        enum ThrustState
        {
            THRUST,
            THRUST_F
        }thrustState;
        enum BrakeState
        {
            BRAKE,
            BRAKE_F

        }brakeState;
};

#endif // PLAYER_H
