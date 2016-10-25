#ifndef CAM_H
#define CAM_H

#include "includes.h"


class cam
{
    public:
        cam(sf::Vector2f pos, sf::Vector2f cameraDimension);
        void follow(sf::Vector2f point);
        void frame();
        sf::View getView();

        sf::View camView;
        sf::Vector2f v2f_Position;
        sf::Vector2f v2f_FocalPoint;
        sf::Vector2f v2f_CamDim;
        virtual ~cam();
    protected:
    private:
};

#endif // CAM_H
