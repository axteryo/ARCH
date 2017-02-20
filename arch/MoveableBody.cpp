#include "MoveableBody.h"


MoveableBody::MoveableBody()
{
    //bodyDef.fixedRotation = true;
    bodyDef.type = b2_dynamicBody;
   // bodyDef.position.Set(100000,-100000);
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
    container->b2V_velocity+=container->b2V_acceleration;
    if(sqrt((container->b2V_velocity.x*container->b2V_velocity.x)
            +(container->b2V_velocity.y*container->b2V_velocity.y))
            >container->topSpeed)
        {
        /*float mag = sqrt((b2V_velocity.x*b2V_velocity.x)
                        +(b2V_velocity.y*b2V_velocity.y));
        if(mag !=0)
        {
            b2V_velocity.x/=mag;
            b2V_velocity.y/=mag;*/
            container->b2V_velocity.Normalize();
            container->b2V_velocity.x*=container->topSpeed;
            container->b2V_velocity.y*=container->topSpeed;
       // }
        }
    body->SetLinearVelocity(container->b2V_velocity);
    container->b2V_position = body->GetPosition();
    body->SetAngularVelocity(0);
    body->SetTransform(container->b2V_position,container->fl_rotation);

}
void MoveableBody::applyImpact(Actor::ImpactState impactType,b2Vec2 direction)
{
    switch(impactType)
    {
    case Actor::PUSHEDBACK:
        body->ApplyForce(b2Vec2(direction.x*1000,direction.y*1000),body->GetWorldCenter(),true);
        std::cout<<"Got hit got hit"<<std::endl;
        break;
        case Actor::PULLED:
            body->ApplyForce(b2Vec2(direction.x*60,direction.y*60),body->GetWorldCenter(),true);
        break;
        case Actor::NO_IMPACT:
        break;

    }
}
void MoveableBody::update(GameObject* gObj)
{
    ///nothing...


}



MoveableBody::~MoveableBody()
{
     world->DestroyBody(body);
    //dtor
}
