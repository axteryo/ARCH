#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "entity.h"
#include "player.h"



class camera
{
    public:
        camera();
        virtual ~camera();
        void setCoords(sf::Vector2i focal, sf::Vector2f viewSize);
        void setTarget(std::string t);

        void follow(sf::Vector2f point);
        //void frame(sf::Vector2f point1,sf::Vector2f point2);
        void update(entity* e);
        sf::View getView();
        sf::View camView;

        std::string targetID;



    protected:
    private:
        bool isAnchoredX;
        bool isAnchoredY;
        //sf::Vector2f v2f_position;
        sf::Vector2i v2i_focalPoint;
        sf::Vector2f v2f_dimensions;

};

#endif // CAMERA_H
