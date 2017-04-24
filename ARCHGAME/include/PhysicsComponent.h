#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H


#include <iostream>
#include "entity.h"

extern b2World* world;
struct fixtureUserData
{
  std::string data;
  fixtureUserData()
  {
      data = "";
  }
};


///NOTE TO SELF:IMPLEMENT BODY AND FIXTUREDATA
///fixtureData Struct(fixtureType,Entity Type,pointer to fixture possibly...,etc.)
///BodyData = (void*)Entity();
class PhysicsComponent
{
    public:
        PhysicsComponent(b2BodyType t);
        virtual ~PhysicsComponent();
        void setPosition(b2Vec2 p);
        ///sets rotation to a specific angle
        void setRotation(float a);
        /// changes angle of rotation by a specific amount
        void _rotate(float a);
        //virtual float getAcceleration
        float getRotation();
        b2Vec2 getPosition();
        void accelerate(b2Vec2 force);
        void createFixtureRectangle(b2Fixture* f,b2Vec2 dimensions,b2Vec2 position,std::string fixturedata);
        void createFixtureCircle();
        void createFixturePolygon(b2Fixture* f,float shape[],int shapeSize,b2Vec2 position,fixtureUserData* fixtureData);
        States::positionState getCurrentState();
        States::positionState getPreviousState();
        void setTopSpeed(float s);
        void limitVelocity();

        void update();

        b2Body* getBody();
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
        float rotationAmount;
        States::positionState currentState;
        States::positionState previousState;

    private:
};

#endif // PHYSICSCOMPONENT_H
