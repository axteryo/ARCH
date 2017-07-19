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
    camBoundary.setSize(sf::Vector2f(camView.getSize().x+50,camView.getSize().y+50));
    camBoundary.setOrigin(camBoundary.getSize().x/2,camBoundary.getSize().y/2);

    camBoundary.setOutlineColor(sf::Color::Magenta);
    camBoundary.setFillColor(sf::Color::Transparent);
    camBoundary.setOutlineThickness(10);
    //1.25
    //1.45
    //1.65
}

bool camera::withinView(sf::Vector2f point)
{
    if(camBoundary.getGlobalBounds().contains(point.x,point.y))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void camera::update()
{
    camBoundary.setPosition(camView.getCenter());
    sf::Vector2f point = sf::Vector2f(0,0);
    if(target)
    {
        if(target->getType().compare("actor")==0)
        {
            ActorEntity* a;
            a = static_cast<ActorEntity*>(target);
            positionState  state = a->getCurrentState();
            sf::Vector2f pos = State::to_v2f(state.position);
            sf::Vector2f vel = State::to_v2f(state.velocity);
            float r = state.rotation;
            int length = 200;
            float vel_percent = 0.05;
            int rate = 20;

            if(!a->isBoosting())
            {
                float vel_percent = .4;
            }
            if(a->isAccelerating())
            {
                //length = 200;
                //rate = 20;
            }

            ///cos and sin of r return direction
            point = sf::Vector2f(pos.x+(cos(r)*length)+(vel.x*vel_percent),
                                 pos.y+(sin(r)*length)+(vel.y*vel_percent));

            follow(point,rate);

        }
    }

    camView.setCenter(v2i_focalPoint.x,v2i_focalPoint.y);
}
///Follow function takes a point vector position parameter and changes the focal point of the camera
void camera::follow(sf::Vector2f point,int rate)
{
    float camVel;
    sf::Vector2f direction = sf::Vector2f(point.x - v2i_focalPoint.x,point.y - v2i_focalPoint.y);
    State::v2f_normalize(direction);
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
