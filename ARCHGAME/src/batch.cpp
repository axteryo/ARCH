#include "batch.h"

batch::batch()
{
    //ctor
    v.setPrimitiveType(sf::Quads);
}

batch::~batch()
{
    //dtor

}
void batch::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
     states.transform *=getTransform();
    states.texture= &t;

    target.draw(v,states);
}


