#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include <Box2D/Box2D.h>
#include "entity.h"
#include <iostream>

extern b2World* world;

namespace States
{
   struct positionState
   {
       b2Vec2 position;
       b2Vec2 velocity;
       b2Vec2 acceleration;
       float rotation;
   };
   struct renderState
   {
       sf::Vector2f position;
       float rotation;
   };
   float to_degrees(float f);
   float to_radians(float f);
   b2Vec2 to_b2v(sf::Vector2f v);
   sf::Vector2f to_v2f(b2Vec2 b);
   renderState to_renderState(positionState p);
   positionState to_positionState(renderState r);

}




class PhysicsComponent
{
    public:
        PhysicsComponent();
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
        States::positionState getCurrentState();
        States::positionState getPreviousState();
        void setTopSpeed(float s);
        void limitVelocity();

        void update(float dt);
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
