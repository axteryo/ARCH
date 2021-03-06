#include "ActorEntity.h"


std::stack<entity*> deathStack;

ActorEntity::ActorEntity(std::string e_ID,GraphicsComponent* g,PhysicsComponent* p, InputComponent* i,StateComponent* s,ActionComponent* a,GameEventListener* eListener)
{
    entity_ID = e_ID;
    entityType = "actor";
    graphics_component = g;
    physics_component = p;
    input_component = i;
    state_component = s;
    action_component = a;
    deathFlag = 0;


    physics_component->getBody()->SetUserData((void*)this);
    _listener = eListener;
}

ActorEntity::~ActorEntity()
{
    delete graphics_component;
    delete physics_component;
    delete input_component;
    delete action_component;
    delete state_component;
}
GraphicsComponent* ActorEntity::getGraphics()
{
    return graphics_component;
}

StateComponent* ActorEntity::getStates()
{
    return state_component;
}
ActionComponent* ActorEntity::getActions()
{
    return action_component;
}

float ActorEntity::getTopSpeed()
{
    return physics_component->getTopSpeed();
}

/**UPDATE FUNCTION**/
void ActorEntity::update()
{
        state_component->update(this);
        input_component->processInput(this);
        action_component->update(this);
        physics_component->update();
        graphics_component->update(this);
        state_component->setPositionState(physics_component->getCurrentState());
        state_component->setRenderState(graphics_component->getCurrentState());
        if(deathFlag>0)
        {
            deathStack.push(this);
            physics_component->getBody()->SetActive(false);
            GameEvent_Entity* eEvent = new GameEvent_Entity(this,EntityState::ENTITY_DIED);
            _listener->notifyEvent(eEvent);
            //world->DestroyBody(physics_component->getBody());
            //deathFlag = 0;
        }
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
bool ActorEntity::isBoosting()
{
    return state_component->getMovementAttributeState().isBoosting;
}
bool ActorEntity::inGridMode()
{
    return state_component->getMovementAttributeState().inGridMode;
}


void ActorEntity::notifyEntityNearby(entity* e)
{
     input_component->onNotifyEntityNearby(e);
}
void ActorEntity::notifyEntityWithinRadius(entity* e)
{
    input_component->onNotifyEntityWithinRadius(e);
}
void ActorEntity::notifyBodyCollision(entity* e)
{
    input_component->onNotifyBodyCollision(e);
}



void ActorEntity::initiateCollision(entity* other, fixtureUserData* otherFData, fixtureUserData* selfFData)
{

    ///Actor to Actor collision
    if(other!=nullptr)
    {
        if(otherFData->type.compare("attackFixture")==0)
        {
            ///we were attacked
            if(selfFData->type.compare("bodyFixture")==0)
            {
                if(isBoosting())
                {
                    action_component->cancelAction("boost");

                }
                if(inGridMode())
                {
                    action_component->cancelAction("modeAttack");
                }
                attackFixtureUserData* otherAFData = static_cast<attackFixtureUserData*>(otherFData);

                applyAttackOnSelf(otherAFData);
            }
        }

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
            if(selfFData->type.compare("bodyFixture")==0)
            {
                if(isBoosting())
                {
                    action_component->cancelAction("boost");
                }

               if(inGridMode())
                {
                    action_component->cancelAction("modeAttack");
                }
            }
        }
        //else
    }
        else if(other->getType().compare("object")==0)
        {
             if(otherFData->type.compare("bodyFixture")==0)
            {

                if(selfFData->type.compare("bodyFixture")==0)
                {

                    if(isBoosting())
                    {
                        action_component->cancelAction("boost");
                    }

                   if(inGridMode())
                    {
                        action_component->cancelAction("modeAttack");
                    }

                }
            }
        }
    }

}

void ActorEntity::playAnimation(std::string animation, bool byTag)
{
    if(byTag)
    {
        graphics_component->onPlayAnimationByTag(animation);
    }
    else
    {
        graphics_component->onPlayAnimation(animation);
    }

}

void ActorEntity::applyAttackOnSelf(attackFixtureUserData* a)
{
    impactAttributeState i = state_component->getImpactAttributeState();
    i.force = a->force;
    i.impactDamage = a->damage;
    i.impactDuration = a->impactDuration;
    i.impactType = a->impactType;
    if(a->attackType.compare("radiusAttack")==0)
    {
        i.direction = getPosition()-a->direction;
    }
    else
    {
        i.direction = a->direction;
    }
    i.isImpacted = true;
    state_component->setImpactAttributeState(i);
}

