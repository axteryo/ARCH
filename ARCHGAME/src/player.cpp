#include "player.h"

player::player(GraphicsComponent* g,PhysicsComponent* p)
{
    entity_ID = "entity_player";
    gComponent = g;
    pComponent = p;
    //ctor
}

player::~player()
{
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

}
GraphicsComponent* player::getGraphic()
{
    return gComponent;
}


std::string player::getID()
{
    return entity_ID;
}
