#include "RadiusBody.h"

RadiusBody::RadiusBody(int radius)
{
    //ctor
    radiusShape.m_p.Set(0,0);
    radiusShape.m_radius = radius/30;
    radiusFixtureDef.shape = &radiusShape;
    radiusFixtureDef.density = 0;
    radiusFixtureDef.isSensor = true;
    fixtureData = new fixtureUserData;

}
void RadiusBody::create(PhysicsBody* p,std::string f_data)
{
    fixtureData->data = f_data;
    radiusFixtureDef.userData = ((void*)fixtureData);
    p->body->CreateFixture(&radiusFixtureDef);

}

RadiusBody::~RadiusBody()
{
    delete fixtureData;
    //dtor
}
