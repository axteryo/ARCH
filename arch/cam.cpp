#include "cam.h"


cam::cam(sf::Vector2f pos, sf::Vector2f cameraDimension)
{
    v2f_Position = pos;
    v2f_CamDim = cameraDimension;
    camView = sf::View(v2f_Position,v2f_CamDim);
    v2i_FocalPoint = sf::Vector2i(v2f_CamDim.x/2,v2f_CamDim.y/2);
}
void cam::update()
{
 camView.move(sf::Vector2f(v2i_FocalPoint.x,v2i_FocalPoint.y));
}
void cam::follow(sf::Vector2i point)
{
    v2f_Position = sf::Vector2f(camView.getCenter().x-v2f_CamDim.x/2,camView.getCenter().y-v2f_CamDim.y/2);
    v2i_FocalPoint = sf::Vector2i(camView.getCenter().x,camView.getCenter().y);
    sf::Vector2f direction = sf::Vector2f(point.x - v2i_FocalPoint.x,
                                              point.y - v2i_FocalPoint.y);
    direction = normalize(direction);

    float camVel;
    ///Checks to see whether the player character is a certain distance from the center
    /*if(sqrt(((point.x - v2i_FocalPoint.x)*
            (point.x-v2i_FocalPoint.x)) +
            ((point.y - v2i_FocalPoint.y)*
            (point.y-v2i_FocalPoint.y)))> 2)
             {*/
           ///Will close on player if so
        camVel =( sqrt(((point.x - v2i_FocalPoint.x)*
            (point.x-v2i_FocalPoint.x)) +
            ((point.y - v2i_FocalPoint.y)*
            (point.y-v2i_FocalPoint.y)))/20);
  //          std::cout<<camVel<<std::endl;
//
                v2i_FocalPoint.x=(direction.x*camVel);
                v2i_FocalPoint.y=(direction.y*camVel);
                //ceil(fl_CamVel);

            //std::cout<<v2i_FocalPoint.x<<","<<v2i_FocalPoint.y<<std::endl;


            //v2i_FocalPoint.x = point.x;
            //v2i_FocalPoint.y = point.y;

            //;
           /*}
            else
            {




        //camView.setCenter(v2i_FocalPoint.x,v2i_FocalPoint.y);

            }
*/



}

sf::View cam::getView()
{
    return camView;
}

cam::~cam()
{
    //dtor
}
