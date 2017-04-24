#include "PhysicsComponent.h"

b2World* world = new b2World(b2Vec2(0,0));

PhysicsComponent::PhysicsComponent(b2BodyType t)
{
    currentState.position = b2Vec2(0,0);
    currentState.rotation = 0;
    currentState.acceleration = b2Vec2(0,0);
    currentState.velocity = b2Vec2(0,0);
    previousState = currentState;

    //bodyDef.position.Set(0,0);
    bodyDef.type = t;
    bodyDef.fixedRotation = true;
    body = world->CreateBody(&bodyDef);
    body->SetAngularVelocity(0);


    //body->SetAngularDamping(2.f);
    //body->SetLinearDamping(2.f);
    topSpeed = 0;
    rotationAmount = 0;

    //ctor
}

PhysicsComponent::~PhysicsComponent()
{
    world->DestroyBody(body);
    //dtor
}

void PhysicsComponent::createFixtureRectangle(b2Fixture* f,b2Vec2 dimensions,b2Vec2 position,std::string fixturedata)
{
    b2PolygonShape boxShape;
    boxShape.SetAsBox(dimensions.x,dimensions.y,position,0);
    fixtureDef.shape = &boxShape;
    fixtureDef.friction = 0;
    fixtureDef.density = 1.0f;
    ///insert fixturedata here
    ///insert userdata here

    f =body->CreateFixture(&fixtureDef);
}
void PhysicsComponent::createFixturePolygon(b2Fixture* f,float shape[],int shapeSize,b2Vec2 position,fixtureUserData* fixtureData)
{
    b2PolygonShape polyShape;

    //std::cout<<shapeSize<<std::endl;
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
    fixtureDef.friction = 0;
    fixtureDef.density = 1.0f;
    //fixtureDef.restitution=100.f;
    //fixtureDef.userData = ((void*)fixtureData);
    f = body->CreateFixture(&fixtureDef);

}

void PhysicsComponent::update()
{

    previousState = currentState;


    currentState.rotation+=(rotationAmount);
    currentState.velocity.x+=(currentState.acceleration.x);
    currentState.velocity.y+=(currentState.acceleration.y);

    limitVelocity();

    body->SetLinearVelocity(currentState.velocity);
    currentState.position = body->GetPosition();




    body->SetTransform(currentState.position,currentState.rotation);


    rotationAmount = 0;
    currentState.acceleration = b2Vec2(0,0);

}
void PhysicsComponent::setRotation(float a)
{
    currentState.rotation = a;
}
void PhysicsComponent::_rotate(float a)
{
    rotationAmount = a;
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
