#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include <Box2D/Box2D.h>

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
        virtual void setPosition(b2Vec2 p)=0;
        virtual void setRotation(float a)=0;
        //virtual float getAcceleration
        virtual float getRotation() = 0;
        virtual b2Vec2 getPosition() = 0;
        virtual void accelerate(b2Vec2 force)= 0;
        virtual void createFixtureRectangle(b2Fixture* f,b2Vec2 dimensions,b2Vec2 position,std::string fixturedata) = 0;

        virtual void update(float dt);
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

        States::positionState currentState;
        States::positionState previousState;

    private:
};

#endif // PHYSICSCOMPONENT_H
