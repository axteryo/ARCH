#include "MoveableBody.h"


MoveableBody::MoveableBody()
{
    //bodyDef.fixedRotation = true;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(1.15,1.15);
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
     //-b2Vec2(cos(gObj->fl_rotation),sin(gObj->fl_rotation));



    body->SetLinearVelocity(gObj->b2V_velocity);
    gObj->b2V_position = body->GetPosition();
    body->SetAngularVelocity(0);
    body->SetTransform(gObj->b2V_position,gObj->fl_rotation);



}


MoveableBody::~MoveableBody()
{
    //dtor
}
