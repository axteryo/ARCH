#include "ActorEntity.h"





ActorEntity::ActorEntity(std::string e_ID,GraphicsComponent* g,PhysicsComponent* p, InputComponent* i,StateComponent* s,ActionComponent* a)
{
    entity_ID = e_ID;
    entityType = "actor";
    graphics_component = g;
    physics_component = p;
    input_component = i;
    state_component = s;
    action_component = a;

    physics_component->getBody()->SetUserData((void*)this);
}

ActorEntity::~ActorEntity()
{
    delete graphics_component;
    delete physics_component;
    delete input_component;
    delete state_component;
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
StateComponent* ActorEntity::getStates()
{
    return state_component;
}
ActionComponent* ActorEntity::getActions()
{
    return action_component;
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
    action_component->update(this);
    physics_component->update();
    graphics_component->update(this);
    state_component->update(this);

    state_component->setPositionState(physics_component->getCurrentState());
    state_component->setRenderState(graphics_component->getCurrentState());
}


positionState ActorEntity::getCurrentState()
{
    return physics_component->getCurrentState();
}
positionState ActorEntity::getPreviousState()
{
    return physics_component->getPreviousState();
}

