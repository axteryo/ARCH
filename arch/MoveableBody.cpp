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

void MoveableBody::update(Actor* container)
{
    /**

    container.vel+= 2;

    body.setvel(container.vel)

    container.position = body.position;

    container.vel = body.vel

    graphics.position = container.position;
    **/
     //-b2Vec2(cos(gObj->fl_rotation),sin(gObj->fl_rotation));



    body->SetLinearVelocity(container->b2V_velocity);
    container->b2V_position = body->GetPosition();
    body->SetAngularVelocity(0);
    body->SetTransform(container->b2V_position,container->fl_rotation);



}
void MoveableBody::update(GameObject* gObj)
{
    ///nothing...
}



MoveableBody::~MoveableBody()
{
    //dtor
}
