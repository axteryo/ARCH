#ifndef ANIMATABLEGRAPHIC_H
#define ANIMATABLEGRAPHIC_H

#include "GraphicsBody.h"
#include "GameObject.h"
#include "Actor.h"
#include "includes.h"


class AnimatableGraphic: public GraphicsBody
{
    public:
        AnimatableGraphic(sf::Texture t);
        virtual ~AnimatableGraphic();
        void update(Actor* container);
        void update(GameObject* gObj);
        sf::Sprite getSprite();
        int height;
        int width;
    protected:
    private:
};

#endif // ANIMATABLEGRAPHIC_H
