#include "cam.h"


cam::cam(sf::Vector2f pos, sf::Vector2f cameraDimension)
{
    v2f_Position = pos;
    v2f_CamDim = cameraDimension;
    camView = sf::View(v2f_Position,v2f_CamDim);
    v2f_FocalPoint = sf::Vector2f(v2f_CamDim.x/2,v2f_CamDim.y/2);
}

void cam::follow(sf::Vector2f point)
{


    sf::Vector2f direction = sf::Vector2f(point.x - v2f_FocalPoint.x,
                                              point.y - v2f_FocalPoint.y);

    float fl_CamVel;

    if(sqrt(((point.x - v2f_FocalPoint.x)*
            (point.x-v2f_FocalPoint.x)) +
            ((point.y - v2f_FocalPoint.y)*
            (point.y - v2f_FocalPoint.y)))>= 10.0)
    {
        fl_CamVel = sqrt(((point.x - v2f_FocalPoint.x)*
            (point.x-v2f_FocalPoint.x)) +
            ((point.y - v2f_FocalPoint.y)*
            (point.y-v2f_FocalPoint.y)))/30.0;

            v2f_FocalPoint.x+=(normalize(direction).x*fl_CamVel);
            v2f_FocalPoint.y+=(normalize(direction).y*fl_CamVel);




    camView.setCenter(v2f_FocalPoint);
    }


}

sf::View cam::getView()
{
    return camView;
}

cam::~cam()
{
    //dtor
}
