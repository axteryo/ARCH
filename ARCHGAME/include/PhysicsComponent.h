#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include <Box2D/Box2D.h>
#include "entity.h"

extern b2World* world;

namespace States
{
   struct positionState
   {
       b2Vec2 postion;
       b2Vec2 velocity;
       b2Vec2 acceleration;
       float rotation;
   };
}




class PhysicsComponent
{
    public:
        PhysicsComponent();
        virtual ~PhysicsComponent();
        void setPosition(b2Vec2 p);
        void setRotation(float a);
        //virtual float getAcceleration
        float getRotation();
        b2Vec2 getPosition();
        void accelerate(b2Vec2 force);
        void createFixtureRectangle(b2Fixture* f,b2Vec2 dimensions,b2Vec2 position,std::string fixturedata);
        States::positionState getCurrentState();
        States::positionState getPreviousState();
        void setTopSpeed(float s);

        void update(entity* e,float dt);
        /***
        virtual void createFixtureCircle() = 0;
        virtual void createFixtureFromPoints()= 0;
        virtual void destroyFixture() = 0;
        ***/



    protected:
        /**Physics Body definitions**/
        b2BodyDef bodyDef;
        b2Body* body;
        b2PolygonShape polygonShape;
        b2FixtureDef fixtureDef;

        float topSpeed;
        States::positionState currentState;
        States::positionState previousState;

    private:
};

#endif // PHYSICSCOMPONENT_H
