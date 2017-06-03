#include "StateComponent.h"
#include "ActorEntity.h"

void State::v2f_normalize(sf::Vector2f &source)
{
    float mag = sqrt((source.x * source.x) + (source.y * source.y));
    if (mag != 0)
    {
        source = sf::Vector2f(source.x / mag, source.y / mag);
        //return source;
    }
}
float State::to_degrees(float f)
{
    return f*(180/3.141592);
}
float State::to_radians(float f)
{
    return f*(3.141592/180);
}
b2Vec2 State::to_b2v(sf::Vector2f v)
{
    return b2Vec2(v.x/30.0,v.y/30);
}
sf::Vector2f State::to_v2f(b2Vec2 b)
{
    return sf::Vector2f(b.x*30.0,b.y*30.0);
}
sf::Vector2i State::to_v2i(b2Vec2 b)
{
    return sf::Vector2i(b.x*30.0,b.y*30.0);
}
renderState State::to_renderState(positionState p)
{
    renderState r;
    r.position = sf::Vector2f(p.position.x*30.0,p.position.y*30.0);
    r.rotation=p.rotation*(180/3.141592);
    return r;
}
positionState State::to_positionState(renderState r)
{
    positionState p;
    p.position = b2Vec2(r.position.x/30.0,r.position.y/30);
    p.rotation*(3.141592/180);
    return p;
}

renderState State::lerpRenderState(renderState pre, renderState cur, double val)
{
    renderState state;


    state.position.x = (cur.position.x*val+pre.position.x*(1.0f-val));
    state.position.y = (cur.position.y*val+pre.position.y*(1.0f-val));
    state.rotation = (cur.rotation*val+pre.rotation*(1.0f-val));
    //state.acceleration = cur.acceleration;
    //state.velocity = cur.velocity;
    return state;
}
positionState State::lerpPositionState(positionState pre, positionState cur, float val)
{
    positionState state;

    state.position.x = cur.position.x*val+pre.position.x*(1.0-val);
    state.position.y = cur.position.y*val+pre.position.y*(1.0-val);
    state.rotation = cur.rotation*val+pre.rotation*(1.0-val);
    state.acceleration = cur.acceleration;
    state.velocity = cur.velocity;
    return state;
}

float State::getDistance(b2Vec2 p1, b2Vec2 p2)
{
    float distance = ((p2.x-p1.x)*(p2.x-p1.x))+((p2.y-p1.y)*(p2.y-p1.y));
    return sqrt(distance);
}

StateComponent::StateComponent()
{
    status_attributeState.curHealth=0;
    status_attributeState.maxHealth=0;
    status_attributeState.minHealth=0;
    status_attributeState.isAlive = false;

    movement_attributeState.accel=0;
    movement_attributeState.accelRate=0;
    movement_attributeState.accelRateLimit=0;
    movement_attributeState.accel_rotationRate=0;
    movement_attributeState.brakeLimit=0;
    movement_attributeState.isAccelerating=false;
    movement_attributeState.isRotating=false;
    movement_attributeState.isBoosting=false;
    movement_attributeState.isBraking=false;
    movement_attributeState.inGridMode = false;
    movement_attributeState.rotationRate=0;
    movement_attributeState.velLimit=0;

    impact_attributeState.isImpacted = false;
    impact_attributeState.force = 0;
    impact_attributeState.impactDamage=0;
    impact_attributeState.impactDuration=0;
    impact_attributeState.impactType="";
    impact_attributeState.direction= b2Vec2(0,0);

    attack_attributeState.attack = "";
    attack_attributeState.damage=0;
    attack_attributeState.direction= b2Vec2(0,0);
    attack_attributeState.force = 0;
    attack_attributeState.impactDuration=0;
    attack_attributeState.impactType="";
    attack_attributeState.isAttacking = false;
    attack_attributeState.rotationRate=0;
}

StateComponent::~StateComponent()
{
    //dtor
}

void StateComponent::setPositionState(positionState p)
{
    position_state = p;
}
void StateComponent::setRenderState(renderState r)
{
    render_state = r;
}
void StateComponent::setMovementAttributeState(movementAttributeState m)
{
    movement_attributeState = m;
}
void StateComponent::setStatusAttributeState(statusAttributeState s)
{
    status_attributeState = s;
}
void StateComponent::setAttackAttributeState(attackAttributeState a)
{
    attack_attributeState=a;
}
void StateComponent::setImpactAttributeState(impactAttributeState i)
{
    impact_attributeState = i;
}

positionState StateComponent::getPositionState()
{
    return position_state;
}
renderState StateComponent::getRenderState()
{
    return render_state;
}
movementAttributeState StateComponent::getMovementAttributeState()
{
    return movement_attributeState;
}
statusAttributeState StateComponent::getStatusAttributeState()
{
    return status_attributeState;
}
attackAttributeState StateComponent::getAttackAttributeState()
{
    return attack_attributeState;
}
impactAttributeState StateComponent::getImpactAttributeState()
{
    return impact_attributeState;
}

void StateComponent::update(ActorEntity* a)
{

    ///Applies impact effect and damage
    if(impact_attributeState.isImpacted)
    {
        b2Vec2 dir = b2Vec2(0,0);
        if(impact_attributeState.impactDuration<=0)
        {
            impact_attributeState.isImpacted = false;
        }
        b2Vec2 force = b2Vec2(0,0);
        if(impact_attributeState.impactType.compare("push")==0)
        {
            force.x = impact_attributeState.force;
            force.y = impact_attributeState.force;
        }
        else if(impact_attributeState.impactType.compare("pull")==0)
        {
            force.x = -impact_attributeState.force;
            force.y = -impact_attributeState.force;
        }
        impact_attributeState.direction.Normalize();
        force.x*=impact_attributeState.direction.x;
        force.y*=impact_attributeState.direction.y;

        a->getPhysics()->accelerate(force);
        impact_attributeState.impactDuration--;
        std::cout<< status_attributeState.curHealth<<std::endl;
        status_attributeState.curHealth-=impact_attributeState.impactDamage;
        impact_attributeState.impactDamage=0;
    }
    ///checks health status
    if(status_attributeState.curHealth<=status_attributeState.minHealth)
    {
        status_attributeState.curHealth = 0;
        status_attributeState.isAlive = false;
    }
    else
    {
        status_attributeState.isAlive =true;
    }


}






