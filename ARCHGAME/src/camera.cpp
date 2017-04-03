#include "camera.h"

camera::camera()
{
    isAnchoredX = false;
    isAnchoredY = false;
    targetID = "";
}
void camera::setCoords(sf::Vector2i focal, sf::Vector2f viewSize)
{
    v2i_focalPoint = focal;
    v2f_dimensions = sf::Vector2f(viewSize.x/2,viewSize.y/2);
    camView = sf::View(sf::Vector2f(v2i_focalPoint.x,v2i_focalPoint.y),viewSize);
    camView.zoom(1.25);
}

void camera::update(entity* e)
{
    sf::Vector2f point = sf::Vector2f(0,0);
    if(targetID.compare("entity_player")==0)
    {
        player* p;
        p = static_cast<player*>(e);
        States::positionState  s = p->getPhysics()->getCurrentState();
        sf::Vector2f pos = States::to_v2f(s.position);
        sf::Vector2f vel = States::to_v2f(s.velocity);
        float r = s.rotation;
        point = sf::Vector2f(pos.x+(cos(r)*50)+(vel.x*.15),
                             pos.y+(sin(r)*50)+(vel.y*.15));

            follow(point);


        //std::cout<<"got here"<<std::endl;


    }
    camView.setCenter(v2i_focalPoint.x,v2i_focalPoint.y);
}
///Follow function takes a point vector position parameter and changes the focal point of the camera
void camera::follow(sf::Vector2f point)
{
    float camVel;
    sf::Vector2f direction = sf::Vector2f(point.x - v2i_focalPoint.x,point.y - v2i_focalPoint.y);
    States::v2f_normalize(direction);
    camVel =sqrt(((point.x - v2i_focalPoint.x)*
            (point.x-v2i_focalPoint.x)) +
            ((point.y - v2i_focalPoint.y)*
            (point.y-v2i_focalPoint.y)))/20;

    v2i_focalPoint.x+=(direction.x*camVel);
    v2i_focalPoint.y+=(direction.y*camVel);
}
void camera::setTarget(std::string t)
{
    targetID = t;
}
camera::~camera()
{
    //dtor
}
