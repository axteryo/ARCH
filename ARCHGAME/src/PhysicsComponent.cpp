#include "PhysicsComponent.h"

b2World* world = new b2World(b2Vec2(0,0));

PhysicsComponent::PhysicsComponent()
{
    currentState.postion = b2Vec2(0,0);
    currentState.rotation = 0;
    currentState.acceleration = b2Vec2(0,0);
    currentState.velocity = b2Vec2(0,0);
    previousState = currentState;
    bodyDef.type = b2_dynamicBody;
    body = world->CreateBody(&bodyDef);
    float topSpeed = 0;
    //ctor
}

PhysicsComponent::~PhysicsComponent()
{
    //dtor
}

void PhysicsComponent::createFixtureRectangle(b2Fixture* f,b2Vec2 dimensions,b2Vec2 position,std::string fixturedata)
{
    b2PolygonShape boxShape;
    boxShape.SetAsBox(dimensions.x,dimensions.y);
    fixtureDef.shape = &boxShape;
    fixtureDef.friction = 0.0f;
    fixtureDef.density = 2.0f;
    ///insert fixturedata here
    ///insert userdata here
    body->CreateFixture(&fixtureDef);

}

void PhysicsComponent::update(entity* e, float dt)
{
    currentState.velocity.x+=currentState.acceleration.x *dt;
    currentState.velocity.y+=currentState.acceleration.y *dt;

    if(sqrt((currentState.velocity.x*currentState.velocity.x)
            +(currentState.velocity.y*currentState.velocity.y))
            > topSpeed)
    {
        currentState.velocity.Normalize();
        currentState.velocity.x*=topSpeed;
        currentState.velocity.y*=topSpeed;
    }
    body->SetLinearVelocity(currentState.velocity);
    currentState.postion = body->GetPosition();
    body->SetAngularVelocity(0);
    body->SetTransform(currentState.postion,currentState.rotation);
    previousState = currentState;
}
void PhysicsComponent::setRotation(float a)
{
    currentState.rotation = a;
}
float PhysicsComponent::getRotation()
{
    return currentState.rotation;
}
void PhysicsComponent::setPosition(b2Vec2 p)
{
    currentState.postion = p;
}
b2Vec2 PhysicsComponent::getPosition()
{
    return currentState.postion;
}

void PhysicsComponent::accelerate(b2Vec2 force)
{
    currentState.acceleration+=force;
}

States::positionState PhysicsComponent::getCurrentState()
{
    return currentState;
}
States::positionState PhysicsComponent::getPreviousState()
{
    return previousState;
}

void PhysicsComponent::setTopSpeed(float s)
{
    topSpeed = s;
}
