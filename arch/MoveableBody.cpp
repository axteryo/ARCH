#include "MoveableBody.h"


MoveableBody::MoveableBody()
{
    bodyDef.fixedRotation = true;
    bodyDef.type = b2_dynamicBody;
    body = world->CreateBody(&bodyDef);

    b2V2f_velocity = b2Vec2(0,0);
    b2V2f_position = b2Vec2(0,0);
}

void MoveableBody::update(GameObject* gObj)
{
      /**

    container.vel+= 2;

    body.setvel(container.vel)

    container.position = body.position;

    container.vel = body.vel

    graphics.position = container.position;
    **/
   // body->SetTransform(gObj->b2V_position,body->GetAngle());
   b2V2f_velocity = gObj->b2V_velocity;

}


MoveableBody::~MoveableBody()
{
    //dtor
}
