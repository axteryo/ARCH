#ifndef CAMERA_H
#define CAMERA_H

#include "ActorEntity.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>




class camera
{
    public:
        camera();
        virtual ~camera();
        void setCoords(sf::Vector2i focal, sf::Vector2f viewSize);
        void setTarget(entity* e);

        void follow(sf::Vector2f point,int rate);
        //void frame(sf::Vector2f point1,sf::Vector2f point2);
        void update();
        sf::View getView();
        sf::View camView;

        std::string targetID;
        entity* target;



    protected:
    private:
        bool isAnchoredX;
        bool isAnchoredY;
        //sf::Vector2f v2f_position;
        sf::Vector2i v2i_focalPoint;
        sf::Vector2f v2f_dimensions;

};

#endif // CAMERA_H
