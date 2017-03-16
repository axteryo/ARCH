#include "player.h"
#include "playerInputComponent.h"

player::player(GraphicsComponent* g,PhysicsComponent* p)
{
    entity_ID = "entity_player";
    gComponent = g;
    pComponent = p;
    inputComponent = new playerInputComponent;
    thrustRate = 0;
    turnRate = 0;
    pComponent->setTopSpeed(30);
    //ctor
}

player::~player()
{
    delete gComponent;
    delete pComponent;
    //dtor
}
void player::setPosition(b2Vec2 p)
{
    pComponent->setPosition(p);
}
b2Vec2 player::getPosition()
{
    return pComponent->getPosition();
}
void player::setRotation(float a)
{
    pComponent->setRotation(a);
}
float player::getRotation()
{
    return pComponent->getRotation();
}

void player::update(float dt)
{
    inputComponent->processInput(this);
    switch(tLeftState)
    {
        case TURN_LEFT:
        ///Player turning Left
            turnLeft();
        break;
        case TURN_LEFT_F:
        break;
    }
    switch(tRightState)
    {
        case TURN_RIGHT:
        ///Player turning Left
            turnRight();
        break;
        case TURN_RIGHT_F:
        break;
    }
    switch(thrustState)
    {
    case THRUST:
        turnRate = 3;
        thrust();
        break;
    case THRUST_F:
        turnRate = 10;
        thrustRate = 0;
        break;
    }
    switch(brakeState)
    {
    case BRAKE:
        brake();
        break;
    case BRAKE_F:
        pComponent->setTopSpeed(30);
        break;
    }
    pComponent->update(dt);
}
GraphicsComponent* player::getGraphic()
{
    return gComponent;
}


std::string player::getID()
{
    return entity_ID;
}


/*** STATE SETTING FUNCTIONS ***/

void player::setTurnRightState()
{
    tRightState = TURN_RIGHT;
}
void player::setTurnRightStateFalse()
{
    tRightState = TURN_RIGHT_F;
}
void player::setTurnLeftState()
{
    tLeftState = TURN_LEFT;
}
void player::setTurnLeftStateFalse()
{
    tLeftState = TURN_LEFT_F;
}
void player::setThrustState()
{
    thrustState = THRUST;
}
void player::setThrustStateFalse()
{
    thrustState = THRUST_F;
}
void player::setBrakeState()
{
    brakeState = BRAKE;
}
void player::setBrakeStateFalse()
{
    brakeState = BRAKE_F;
}



/*** ACTION FUNCTIONS ***/

void player::turnRight()
{
    float rate = turnRate;
    pComponent->_rotate(turnRate);
}
void player::turnLeft()
{
    float rate = -turnRate;
    pComponent->_rotate(rate);
}
void player::thrust()
{
    float r = getRotation();
    b2Vec2 aim(0,0);
    //turnRate =.04;
    if(thrustRate<150)
    {
        thrustRate += 5;
    }
    else
    {
        thrustRate = 150;
    }
    //thrustRate=;
    aim = b2Vec2(cos(r),sin(r));
    aim.Normalize();

    aim.x*=thrustRate;
    aim.y*=thrustRate;
    pComponent->accelerate(aim);
}
void player::brake()
{
    pComponent->setTopSpeed(10);
    //pComponent->limitVelocity();
}
