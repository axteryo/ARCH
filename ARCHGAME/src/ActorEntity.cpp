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
movementAttributeState ActorEntity::getMovementAttributeState()
{
    return state_component->getMovementAttributeState();
}
statusAttributeState ActorEntity::getStatusAttributeState()
{
    return state_component->getStatusAttributeState();
}
attackAttributeState ActorEntity::getAttackAttributeState()
{
    return state_component->getAttackAttributeState();
}
impactAttributeState ActorEntity::getImpactAttributeState()
{
    return state_component->getImpactAttributeState();
}
bool ActorEntity::isAttacking()
{
    return state_component->getAttackAttributeState().isAttacking;
}
bool  ActorEntity::isRotating()
{
     return state_component->getMovementAttributeState().isRotating;
}
bool  ActorEntity::isAlive()
{
    return state_component->getStatusAttributeState().isAlive;
}
bool  ActorEntity::isAccelerating()
{
     return state_component->getMovementAttributeState().isAccelerating;
}
bool  ActorEntity::isImpacted()
{
    return state_component->getImpactAttributeState().isImpacted;
}

positionState ActorEntity::getCurrentState()
{
    return physics_component->getCurrentState();
}
positionState ActorEntity::getPreviousState()
{
    return physics_component->getPreviousState();
}


void ActorEntity::notifyEntityNearby(entity* e)
{
     input_component->onNotifyEntityNearby(e);
}
void ActorEntity::notifyEntityWithinRadius(entity* e)
{
    input_component->onNotifyEntityWithinRadius(e);
}


void ActorEntity::initiateCollision(entity* other, fixtureUserData* otherFData, fixtureUserData* selfFData)
{

    ///Actor to Actor collision
    if(other->getType().compare("actor")==0)
    {
        ActorEntity* otherActor = static_cast<ActorEntity*>(other);
        notifyEntityNearby(otherActor);

        if(otherFData->type.compare("bodyFixture")==0)
        {
            if(selfFData->type.compare("sensorFixture")==0)
            {
                notifyEntityWithinRadius(otherActor);
            }
        }
        else if(otherFData->type.compare("attackFixture")==0)
        {
            ///we were attacked
            if(selfFData->type.compare("bodyFixture")==0)
            {
                attackAttributeState otherAttackAttributes= otherActor->getAttackAttributeState();
                applyAttackOnSelf(otherAttackAttributes);
            }
        }
    }

}


void ActorEntity::applyAttackOnSelf(attackAttributeState a)
{
    impactAttributeState i = state_component->getImpactAttributeState();
    i.force = a.force;
    i.impactDamage = a.damage;
    i.impactDuration = a.impactDuration;
    i.impactType = a.impactType;
    i.direction = a.direction;
    i.isImpacted = true;
    state_component->setImpactAttributeState(i);
}

