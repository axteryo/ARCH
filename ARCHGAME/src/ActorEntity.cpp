#include "ActorEntity.h"





ActorEntity::ActorEntity(std::string e_ID,GraphicsComponent* g,PhysicsComponent* p, InputComponent* i)
{
    entity_ID = e_ID;
    entityType = "actor";
    graphics_component = g;
    physics_component = p;
    input_component = i;

    physics_component->getBody()->SetUserData((void*)this);
}

ActorEntity::~ActorEntity()
{
    delete graphics_component;
    delete physics_component;
    delete input_component;
    //dtor
}
GraphicsComponent* ActorEntity::getGraphics()
{
    return graphics_component;
}
PhysicsComponent* ActorEntity::getPhysics()
{
    return physics_component;
}

/****BASE ENTITY FUNCTIONS*****/
void ActorEntity::setPosition(b2Vec2 p)
{
    physics_component->setPosition(p);
}
b2Vec2 ActorEntity::getPosition()
{
    return physics_component->getPosition();
}
void ActorEntity::setRotation(float a)
{
    physics_component->setRotation(a);
}
float ActorEntity::getRotation()
{
    return physics_component->getRotation();
}
std::string ActorEntity::getID()
{
    return entity_ID;
}
std::string ActorEntity::getType()
{
    return entityType;
}

/**UPDATE FUNCTION**/
void ActorEntity::update()
{
    input_component->processInput(this);
    physics_component->update();
    graphics_component->update(this);
}


States::positionState ActorEntity::getCurrentState()
{
    return physics_component->getCurrentState();
}
States::positionState ActorEntity::getPreviousState()
{
    return physics_component->getPreviousState();
}
States::attributeState ActorEntity::getAttributes()
{
    return attributes;
}
void ActorEntity::setAttributes(States::attributeState a)
{
    attributes = a;
}

/*** BASE ACTOR FUNCTIONS**/

///State Functions
void  ActorEntity::setRotateRightState()
{
    rotateRightState =ROTATE_RIGHT;
}
void  ActorEntity::setRotateLeftState()
{
    rotateLeftState =ROTATE_LEFT;
}
void  ActorEntity::setRotateRightStateFalse()
{
    rotateRightState =ROTATE_RIGHT_F;
}
void  ActorEntity::setRotateLeftStateFalse()
{
    rotateLeftState =ROTATE_LEFT_F;
}
void  ActorEntity::setAccelState()
{
    accelState = ACCELERATE;
}
void  ActorEntity::setAccelStateFalse()
{
     accelState = ACCELERATE_F;
     attributes.accel = 0;
}
void  ActorEntity::setBrakeState()
{
    brakeState = BRAKE;
}
void  ActorEntity::setBrakeStateFalse()
{
    brakeState = BRAKE_F;
}
