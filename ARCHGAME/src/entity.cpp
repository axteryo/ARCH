#include "entity.h"

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
    r.rotation=p.rotation*(180/3.141592);
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



entity::entity()
{
    //ctor
}

entity::~entity()
{
    //dtor
}
