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

void camera::update()
{
    sf::Vector2f point = sf::Vector2f(0,0);
    if(target)
    {
        if(target->getID().compare("entity_player")==0)
        {
            player* p;
            p = static_cast<player*>(target);
            States::positionState  s = p->getPhysics()->getCurrentState();
            sf::Vector2f pos = States::to_v2f(s.position);
            sf::Vector2f vel = States::to_v2f(s.velocity);
            float r = s.rotation;
            int length = 200;
            float vel_percent = .5;
            ///cos and sin of r return direction
            point = sf::Vector2f(pos.x+(cos(r)*length)+(vel.x*vel_percent),
                                 pos.y+(sin(r)*length)+(vel.y*vel_percent));

            follow(point,50);

        }
    }

    camView.setCenter(v2i_focalPoint.x,v2i_focalPoint.y);
}
///Follow function takes a point vector position parameter and changes the focal point of the camera
void camera::follow(sf::Vector2f point,int rate)
{
    float camVel;
    sf::Vector2f direction = sf::Vector2f(point.x - v2i_focalPoint.x,point.y - v2i_focalPoint.y);
    States::v2f_normalize(direction);
    camVel =sqrt(((point.x - v2i_focalPoint.x)*
            (point.x-v2i_focalPoint.x)) +
            ((point.y - v2i_focalPoint.y)*
            (point.y-v2i_focalPoint.y)))/rate;

    v2i_focalPoint.x+=(direction.x*camVel);
    v2i_focalPoint.y+=(direction.y*camVel);
}
void camera::setTarget(entity* e)
{
    target = e;
}
camera::~camera()
{
    //dtor
}
