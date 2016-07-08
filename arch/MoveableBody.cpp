#include "MoveableBody.h"


MoveableBody::MoveableBody()
{
    bodyDef.fixedRotation = true;
    bodyDef.type = b2_dynamicBody;
    body = world->CreateBody(&bodyDef);
}

void MoveableBody::update(GameObject& gObj)
{
      /**

    container.vel+= 2;

    body.setvel(container.vel)

    container.position = body.position;

    container.vel = body.vel

    graphics.position = container.position;
    **/

}
MoveableBody::~MoveableBody()
{
    //dtor
}
