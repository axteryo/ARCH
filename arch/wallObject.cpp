#include "wallObject.h"



wallObject::wallObject(unMoveableBody* p, StaticGraphic* g )
{

    b2V_position = b2Vec2(0,0);
    b2V_velocity = b2Vec2(0,0);
    fl_rotation = 0;
   // _graphicsBody =  new GraphicsBody();
    //_physicsBody = new PhysicsBody();

    objectId ="object_wall";
    layerDepth = 5;

    //_graphicsBody = g;
    _physicsBody  = p;
    _graphicsBody = g;

    _physicsBody->body->SetUserData((void*)this);



}
void wallObject::update()
{
    //b2V_velocity = _physicsBody->body->GetLinearVelocity;
    _physicsBody->update(this);
    _graphicsBody->update(this);

}
void wallObject::setPosition(float x, float y)
{
    b2V_position = b2Vec2(x/30,y/30);
}

wallObject::~wallObject()
{
    //dtor
}
sf::Sprite wallObject::getSprite()
{
    return _graphicsBody->getSprite();
}

