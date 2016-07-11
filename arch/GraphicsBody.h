#ifndef GRAPHICSBODY_H
#define GRAPHICSBODY_H

#include "includes.h"


#include "GameObject.h"




class GraphicsBody
{
    public:
        GraphicsBody();
        virtual ~GraphicsBody();
        virtual void update(GameObject* gObj) = 0;
        virtual sf::Sprite getSprite() = 0;
        sf::Texture texture;
        sf::Sprite sprite;
    protected:
    private:

    //

};

#endif  //GRAPHICSBODY_H
