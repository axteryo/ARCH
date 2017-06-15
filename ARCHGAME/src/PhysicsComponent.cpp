#include "PhysicsComponent.h"

b2World* world = new b2World(b2Vec2(0,0));

PhysicsComponent::PhysicsComponent(b2BodyType t)
{
    currentState.position = b2Vec2(0,0);
    currentState.rotation = 0;
    currentState.acceleration = b2Vec2(0,0);
    currentState.velocity = b2Vec2(0,0);

    previousState .position = b2Vec2(0,0);
    previousState .rotation = 0;
    previousState .acceleration = b2Vec2(0,0);
    previousState .velocity = b2Vec2(0,0);


    bodyDef.type = t;
    bodyDef.fixedRotation = true;
    body = world->CreateBody(&bodyDef);

    topSpeed = 0;
    rotationAmount = 0;
    body->SetActive(false);
}

PhysicsComponent::~PhysicsComponent()
{
   world->DestroyBody(body);
}

b2Fixture* PhysicsComponent::createFixtureRectangle(b2Vec2 dimensions,b2Vec2 position,fixtureUserData* fixtureData,bool isSensor)
{
    b2PolygonShape boxShape;
    boxShape.SetAsBox(dimensions.x,dimensions.y,position,0);
    fixtureDef.shape = &boxShape;
    fixtureDef.friction = 0.0;
    fixtureDef.density = 2.0f;
    fixtureDef.userData = ((void*)fixtureData);
    fixtureDef.isSensor = isSensor;
    fixtureDef.restitution= .1;
    b2Fixture* f =body->CreateFixture(&fixtureDef);
    return f;
}
b2Fixture* PhysicsComponent::createFixtureCircle(float radius,b2Vec2 position, fixtureUserData* fixtureData, bool isSensor)
{
    b2CircleShape circleShape;
    circleShape.m_p.Set(position.x,position.y);
    circleShape.m_radius = radius;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 0;
    fixtureDef.userData = ((void*)fixtureData);
    fixtureDef.isSensor = isSensor;
    fixtureDef.restitution= 1;
    b2Fixture* f = body->CreateFixture((&fixtureDef));
    return f;
}
b2Fixture* PhysicsComponent::createFixturePolygon(std::vector<float> shape,b2Vec2 position,fixtureUserData* fixtureData,bool isSensor)
{
    b2PolygonShape polyShape;
    int shapeSize = shape.size();

    b2Vec2 vertices[shapeSize/2];
    int x = shapeSize-2;
    int y = x+1;

    for(int i = 0;i<shapeSize;++i)
    {
        if(x>=0)
        {
            vertices[i].Set((shape[x]-position.x/2)/30.0f,(shape[y]-position.y/2)/30.0f);
            x-=2;
            y=x+1;
        }
    }
    polyShape.Set(vertices,shapeSize/2);
    fixtureDef.shape = &polyShape;
    fixtureDef.friction = 0.0;
    fixtureDef.density = .1;
    fixtureDef.userData = ((void*)fixtureData);
    fixtureDef.isSensor = isSensor;
    fixtureDef.restitution= .01;
    b2Fixture* f;
    f = body->CreateFixture(&fixtureDef);

    return f;
}

void PhysicsComponent::update()
{
    if(!body->IsActive())
    {
        body->SetActive(true);
    }

    previousState = currentState;

    //currentState.rotation+=(rotationAmount);
    currentState.velocity = body->GetLinearVelocity();
    currentState.velocity.x+=(currentState.acceleration.x);
    currentState.velocity.y+=(currentState.acceleration.y);

    limitVelocity();

    body->SetLinearVelocity(currentState.velocity);
    body->SetAngularVelocity(rotationAmount);
    currentState.position = body->GetPosition();
    currentState.rotation = body->GetAngle();

    body->SetTransform(currentState.position,currentState.rotation);

    rotationAmount = 0;
    currentState.acceleration = b2Vec2(0,0);

}
void PhysicsComponent::setRotation(float a)
{
    currentState.rotation = a;
    body->SetTransform(body->GetPosition(),a);
}
void PhysicsComponent::_rotate(float a)
{
    rotationAmount += a;
}
float PhysicsComponent::getRotation()
{
    return currentState.rotation;
}
void PhysicsComponent::setPosition(b2Vec2 p)
{
    currentState.position = p;
    body->SetTransform(p,body->GetAngle());
}
b2Vec2 PhysicsComponent::getPosition()
{
    return currentState.position;
}
void PhysicsComponent::accelerate(b2Vec2 force)
{
    currentState.acceleration+=force;
}
positionState PhysicsComponent::getCurrentState()
{
    return currentState;
}
positionState PhysicsComponent::getPreviousState()
{
    return previousState;
}

void PhysicsComponent::setTopSpeed(float s)
{
    topSpeed = s;
}

float PhysicsComponent::getTopSpeed()
{
    return topSpeed;
}

void PhysicsComponent::limitVelocity()
{
    if(currentState.velocity.Length()> topSpeed)
    {
        currentState.velocity.Normalize();
        currentState.velocity.x*=topSpeed;
        currentState.velocity.y*=topSpeed;
    }
}

b2Body* PhysicsComponent::getBody()
{
    return body;
}

void PhysicsComponent::applyForce(b2Vec2 force)
{
    body->ApplyForce(force,body->GetWorldCenter(),true);
}
