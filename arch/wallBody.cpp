#include "wallBody.h"
#include "ArchGame.h"

wallBody::wallBody()
{


}
void wallBody::create(sf::Sprite sprite)
{
    bodyDef.fixedRotation = true;
    bodyDef.type = b2_staticBody;
    body = world->CreateBody(&bodyDef);
    polygonShape.SetAsBox((sprite.getPosition().x/2)/30,
                          (sprite.getPosition().y/2)/30);
    fixtureDef.shape = polygonShape;
    fixtureDef.density = 100.0f;
    fixtureDef.friction = 0.0f;
    body->CreateFixture(&fixtureDef);


}
void wallBody::update(GameObject& go)
{

}


wallBody::~wallBody()
{
    //dtor
}
