#include "cam.h"


cam::cam(sf::Vector2f pos, sf::Vector2f cameraDimension)
{
    v2f_Position = pos;
    v2f_CamDim = cameraDimension;
    camView = sf::View(v2f_Position,v2f_CamDim);
    v2f_FocalPoint = sf::Vector2i(v2f_CamDim.x/2,v2f_CamDim.y/2);
}

void cam::follow(sf::Vector2f point)
{


    sf::Vector2f direction = sf::Vector2f(point.x - v2f_FocalPoint.x,
                                              point.y - v2f_FocalPoint.y);

    float fl_CamVel;
    ///Checks to see whether the player character is a certain distance from the center
    if(ceil(sqrt(((point.x - v2f_FocalPoint.x)*
            (point.x-v2f_FocalPoint.x)) +
            ((point.y - v2f_FocalPoint.y)*
            (point.y - v2f_FocalPoint.y))))> 1.0)
    {
        ///Will close on player if so
        fl_CamVel = sqrt(((point.x - v2f_FocalPoint.x)*
            (point.x-v2f_FocalPoint.x)) +
            ((point.y - v2f_FocalPoint.y)*
            (point.y-v2f_FocalPoint.y)))/20.0;

            //ceil(fl_CamVel);

            direction = normalize(direction);
            v2f_FocalPoint.x+=direction.x*fl_CamVel;
            v2f_FocalPoint.y+=direction.y*fl_CamVel;




    camView.setCenter(v2f_FocalPoint.x,v2f_FocalPoint.y);
    }
    else
    {
        v2f_FocalPoint.x = point.x;
        v2f_FocalPoint.y = point.y;
        camView.setCenter(v2f_FocalPoint.x,v2f_FocalPoint.y);
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
