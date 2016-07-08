#include "unMoveableBody.h"

unMoveableBody::unMoveableBody()
{
    bodyDef.fixedRotation = true;
    bodyDef.type = b2_kinematicBody;
    body = world->CreateBody(&bodyDef);

    b2V2f_velocity = b2Vec2(0,0);
    b2V2f_position = b2Vec2(0,0);

}
void unMoveableBody::update(GameObject& gObj)
{
    //body->SetLinearVelocity(gObj.b2V_velocity);
    gObj.b2V_position = body->GetPosition();
}

unMoveableBody::~unMoveableBody()
{
    //dtor
}
