#include "wallObject.h"



wallObject::wallObject()//,GraphicsBody() g)
{

    b2V_position = b2Vec2(0,0);
    b2V_velocity = b2Vec2(0,0);
    b2V_rotation = b2Vec2(0,0);
   // _graphicsBody =  new GraphicsBody();
    //_physicsBody = new PhysicsBody();

    objectId ="object_wall";
    layerDepth = 5;

    //_graphicsBody = g;
    _physicsBody  =  new unMoveableBody();



}
void wallObject::update()
{
    //b2V_velocity = _physicsBody->body->GetLinearVelocity;
    _physicsBody->update(this);
   // _graphicsBody->update(this);

}
void wallObject::setPosition()
{
    ///
}

wallObject::~wallObject()
{
    //dtor
}

