#include "PhysicsComponent.h"

b2World* world = new b2World(b2Vec2(0,0));

void States::v2f_normalize(sf::Vector2f &source)
{
    float mag = sqrt((source.x * source.x) + (source.y * source.y));
    if (mag != 0)
    {
        source = sf::Vector2f(source.x / mag, source.y / mag);
        //return source;
    }
}
float States::to_degrees(float f)
{
    return f*(180/3.141592);
}
float States::to_radians(float f)
{
    return f*(3.141592/180);
}
b2Vec2 States::to_b2v(sf::Vector2f v)
{
    return b2Vec2(v.x/30.0,v.y/30);
}
sf::Vector2f States::to_v2f(b2Vec2 b)
{
    return sf::Vector2f(b.x*30.0,b.y*30.0);
}
sf::Vector2i States::to_v2i(b2Vec2 b)
{
    return sf::Vector2i(b.x*30.0,b.y*30.0);
}
States::renderState States::to_renderState(States::positionState p)
{
    States::renderState r;
    r.position = sf::Vector2f(p.position.x*30.0,p.position.y*30.0);
    r.rotation*(180/3.141592);
    return r;
}
States::positionState States::to_positionState(States::renderState r)
{
    States::positionState p;
    p.position = b2Vec2(r.position.x/30.0,r.position.y/30);
    p.rotation*(3.141592/180);
    return p;
}

States::renderState States::lerpRenderState(States::renderState pre, States::renderState cur, double val)
{
    States::renderState state;


    state.position.x = (cur.position.x*val+pre.position.x*(1.0f-val));
    state.position.y = (cur.position.y*val+pre.position.y*(1.0f-val));
    state.rotation = (cur.rotation*val+pre.rotation*(1.0f-val));
    //state.acceleration = cur.acceleration;
    //state.velocity = cur.velocity;
    return state;
}
States::positionState States::lerpPositionState(States::positionState pre, States::positionState cur, float val)
{
    States::positionState state;

    state.position.x = cur.position.x*val+pre.position.x*(1.0-val);
    state.position.y = cur.position.y*val+pre.position.y*(1.0-val);
    state.rotation = cur.rotation*val+pre.rotation*(1.0-val);
    state.acceleration = cur.acceleration;
    state.velocity = cur.velocity;
    return state;
}


PhysicsComponent::PhysicsComponent()
{
    currentState.position = b2Vec2(0,0);
    currentState.rotation = 0;
    currentState.acceleration = b2Vec2(0,0);
    currentState.velocity = b2Vec2(0,0);
    previousState = currentState;
    bodyDef.type = b2_dynamicBody;
    body = world->CreateBody(&bodyDef);
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
    fixtureDef.friction = 0.0f;
    fixtureDef.density = 2.0f;
    ///insert fixturedata here
    ///insert userdata here

    f =body->CreateFixture(&fixtureDef);


}

void PhysicsComponent::update(float dt)
{

    previousState = currentState;

    //currentState.velocity = body->GetLinearVelocity();
    currentState.rotation+=(rotationAmount);
    currentState.velocity.x+=(currentState.acceleration.x);
    currentState.velocity.y+=(currentState.acceleration.y);

    limitVelocity();
    //currentState.position.x +=(currentState.velocity.x*dt);
    //currentState.position.y +=(currentState.velocity.y*dt);
    //currentState.velocity = ;
    body->SetLinearVelocity(currentState.velocity);
    currentState.position = body->GetPosition();




    body->SetTransform(currentState.position,currentState.rotation);
    body->SetAngularVelocity(0);
    //body->SetLinearDamping(0);
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

    /*if(sqrt((currentState.velocity.x*currentState.velocity.x)
            +(currentState.velocity.y*currentState.velocity.y))
             > topSpeed)*/

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
