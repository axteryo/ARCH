#include "StateComponent.h"

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



StateComponent::StateComponent()
{
    //ctor
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




