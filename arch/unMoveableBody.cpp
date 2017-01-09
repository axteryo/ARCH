#include "unMoveableBody.h"

unMoveableBody::unMoveableBody()
{
    bodyDef.fixedRotation = true;
    bodyDef.type = b2_staticBody;
    body = world->CreateBody(&bodyDef);
    //body->SetActive(false);

    //b2V2f_velocity = b2Vec2(0,0);
    b2V2f_position = b2Vec2(0,0);

}
void unMoveableBody::update(GameObject* gObj)
{
    //body->SetLinearVelocity(gObj.b2V_velocity);
    //body->SetActive(true);
    body->SetTransform(gObj->b2V_position,body->GetAngle());
}

unMoveableBody::~unMoveableBody()
{
    world->DestroyBody(body);

}
